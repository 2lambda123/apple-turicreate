#!/usr/bin/env perl

# ====================================================================
# Written by Andy Polyakov <appro@openssl.org> for the OpenSSL
# project. The module is, however, dual licensed under OpenSSL and
# CRYPTOGAMS licenses depending on where you obtain it. For further
# details see http://www.openssl.org/~appro/cryptogams/.
# ====================================================================

# September 2010.
#
# The module implements "4-bit" GCM GHASH function and underlying
# single multiplication operation in GF(2^128). "4-bit" means that it
# uses 256 bytes per-key table [+128 bytes shared table]. Performance
# was measured to be ~18 cycles per processed byte on z10, which is
# almost 40% better than gcc-generated code. It should be noted that
# 18 cycles is worse result than expected: loop is scheduled for 12
# and the result should be close to 12. In the lack of instruction-
# level profiling data it's impossible to tell why...

# November 2010.
#
# Adapt for -m31 build. If kernel supports what's called "highgprs"
# feature on Linux [see /proc/cpuinfo], it's possible to use 64-bit
# instructions and achieve "64-bit" performance even in 31-bit legacy
# application context. The feature is not specific to any particular
# processor, as long as it's "z-CPU". Latter implies that the code
# remains z/Architecture specific. On z990 it was measured to perform
# 2.8x better than 32-bit code generated by gcc 4.3.

# March 2011.
#
# Support for hardware KIMD-GHASH is verified to produce correct
# result and therefore is engaged. On z196 it was measured to process
# 8KB buffer ~7 faster than software implementation. It's not as
# impressive for smaller buffer sizes and for smallest 16-bytes buffer
# it's actually almost 2 times slower. Which is the reason why
# KIMD-GHASH is not used in gcm_gmult_4bit.

$flavour = shift;

if ($flavour =~ /3[12]/) {
	$SIZE_T=4;
	$g="";
} else {
	$SIZE_T=8;
	$g="g";
}

while (($output=shift) && ($output!~/^\w[\w\-]*\.\w+$/)) {}
open STDOUT,">$output";

$softonly=0;

$Zhi="%r0";
$Zlo="%r1";

$Xi="%r2";	# argument block
$Htbl="%r3";
$inp="%r4";
$len="%r5";

$rem0="%r6";	# variables
$rem1="%r7";
$nlo="%r8";
$nhi="%r9";
$xi="%r10";
$cnt="%r11";
$tmp="%r12";
$x78="%r13";
$rem_4bit="%r14";

$sp="%r15";

$code.=<<___;
.text

.globl	gcm_gmult_4bit
.align	32
gcm_gmult_4bit:
___
$code.=<<___ if(!$softonly && 0);	# hardware is slow for single block...
	larl	%r1,OPENSSL_s390xcap_P
	lg	%r0,0(%r1)
	tmhl	%r0,0x4000	# check for message-security-assist
	jz	.Lsoft_gmult
	lghi	%r0,0
	lg	%r1,24(%r1)	# load second word of kimd capabilities vector
	tmhh	%r1,0x4000	# check for function 65
	jz	.Lsoft_gmult
	stg	%r0,16($sp)	# arrange 16 bytes of zero input
	stg	%r0,24($sp)
	lghi	%r0,65		# function 65
	la	%r1,0($Xi)	# H lies right after Xi in gcm128_context
	la	$inp,16($sp)
	lghi	$len,16
	.long	0xb93e0004	# kimd %r0,$inp
	brc	1,.-4		# pay attention to "partial completion"
	br	%r14
.align	32
.Lsoft_gmult:
___
$code.=<<___;
	stm${g}	%r6,%r14,6*$SIZE_T($sp)

	aghi	$Xi,-1
	lghi	$len,1
	lghi	$x78,`0xf<<3`
	larl	$rem_4bit,rem_4bit

	lg	$Zlo,8+1($Xi)		# Xi
	j	.Lgmult_shortcut
.type	gcm_gmult_4bit,\@function
.size	gcm_gmult_4bit,(.-gcm_gmult_4bit)

.globl	gcm_ghash_4bit
.align	32
gcm_ghash_4bit:
___
$code.=<<___ if(!$softonly);
	larl	%r1,OPENSSL_s390xcap_P
	lg	%r0,0(%r1)
	tmhl	%r0,0x4000	# check for message-security-assist
	jz	.Lsoft_ghash
	lghi	%r0,0
	la	%r1,16($sp)
	.long	0xb93e0004	# kimd %r0,%r4
	lg	%r1,24($sp)
	tmhh	%r1,0x4000	# check for function 65
	jz	.Lsoft_ghash
	lghi	%r0,65		# function 65
	la	%r1,0($Xi)	# H lies right after Xi in gcm128_context
	.long	0xb93e0004	# kimd %r0,$inp
	brc	1,.-4		# pay attention to "partial completion"
	br	%r14
.align	32
.Lsoft_ghash:
___
$code.=<<___ if ($flavour =~ /3[12]/);
	llgfr	$len,$len
___
$code.=<<___;
	stm${g}	%r6,%r14,6*$SIZE_T($sp)

	aghi	$Xi,-1
	srlg	$len,$len,4
	lghi	$x78,`0xf<<3`
	larl	$rem_4bit,rem_4bit

	lg	$Zlo,8+1($Xi)		# Xi
	lg	$Zhi,0+1($Xi)
	lghi	$tmp,0
.Louter:
	xg	$Zhi,0($inp)		# Xi ^= inp
	xg	$Zlo,8($inp)
	xgr	$Zhi,$tmp
	stg	$Zlo,8+1($Xi)
	stg	$Zhi,0+1($Xi)

.Lgmult_shortcut:
	lghi	$tmp,0xf0
	sllg	$nlo,$Zlo,4
	srlg	$xi,$Zlo,8		# extract second byte
	ngr	$nlo,$tmp
	lgr	$nhi,$Zlo
	lghi	$cnt,14
	ngr	$nhi,$tmp

	lg	$Zlo,8($nlo,$Htbl)
	lg	$Zhi,0($nlo,$Htbl)

	sllg	$nlo,$xi,4
	sllg	$rem0,$Zlo,3
	ngr	$nlo,$tmp
	ngr	$rem0,$x78
	ngr	$xi,$tmp

	sllg	$tmp,$Zhi,60
	srlg	$Zlo,$Zlo,4
	srlg	$Zhi,$Zhi,4
	xg	$Zlo,8($nhi,$Htbl)
	xg	$Zhi,0($nhi,$Htbl)
	lgr	$nhi,$xi
	sllg	$rem1,$Zlo,3
	xgr	$Zlo,$tmp
	ngr	$rem1,$x78
	sllg	$tmp,$Zhi,60
	j	.Lghash_inner
.align	16
.Lghash_inner:
	srlg	$Zlo,$Zlo,4
	srlg	$Zhi,$Zhi,4
	xg	$Zlo,8($nlo,$Htbl)
	llgc	$xi,0($cnt,$Xi)
	xg	$Zhi,0($nlo,$Htbl)
	sllg	$nlo,$xi,4
	xg	$Zhi,0($rem0,$rem_4bit)
	nill	$nlo,0xf0
	sllg	$rem0,$Zlo,3
	xgr	$Zlo,$tmp
	ngr	$rem0,$x78
	nill	$xi,0xf0

	sllg	$tmp,$Zhi,60
	srlg	$Zlo,$Zlo,4
	srlg	$Zhi,$Zhi,4
	xg	$Zlo,8($nhi,$Htbl)
	xg	$Zhi,0($nhi,$Htbl)
	lgr	$nhi,$xi
	xg	$Zhi,0($rem1,$rem_4bit)
	sllg	$rem1,$Zlo,3
	xgr	$Zlo,$tmp
	ngr	$rem1,$x78
	sllg	$tmp,$Zhi,60
	brct	$cnt,.Lghash_inner

	srlg	$Zlo,$Zlo,4
	srlg	$Zhi,$Zhi,4
	xg	$Zlo,8($nlo,$Htbl)
	xg	$Zhi,0($nlo,$Htbl)
	sllg	$xi,$Zlo,3
	xg	$Zhi,0($rem0,$rem_4bit)
	xgr	$Zlo,$tmp
	ngr	$xi,$x78

	sllg	$tmp,$Zhi,60
	srlg	$Zlo,$Zlo,4
	srlg	$Zhi,$Zhi,4
	xg	$Zlo,8($nhi,$Htbl)
	xg	$Zhi,0($nhi,$Htbl)
	xgr	$Zlo,$tmp
	xg	$Zhi,0($rem1,$rem_4bit)

	lg	$tmp,0($xi,$rem_4bit)
	la	$inp,16($inp)
	sllg	$tmp,$tmp,4		# correct last rem_4bit[rem]
	brctg	$len,.Louter

	xgr	$Zhi,$tmp
	stg	$Zlo,8+1($Xi)
	stg	$Zhi,0+1($Xi)
	lm${g}	%r6,%r14,6*$SIZE_T($sp)
	br	%r14
.type	gcm_ghash_4bit,\@function
.size	gcm_ghash_4bit,(.-gcm_ghash_4bit)

.align	64
rem_4bit:
	.long	`0x0000<<12`,0,`0x1C20<<12`,0,`0x3840<<12`,0,`0x2460<<12`,0
	.long	`0x7080<<12`,0,`0x6CA0<<12`,0,`0x48C0<<12`,0,`0x54E0<<12`,0
	.long	`0xE100<<12`,0,`0xFD20<<12`,0,`0xD940<<12`,0,`0xC560<<12`,0
	.long	`0x9180<<12`,0,`0x8DA0<<12`,0,`0xA9C0<<12`,0,`0xB5E0<<12`,0
.type	rem_4bit,\@object
.size	rem_4bit,(.-rem_4bit)
.string	"GHASH for s390x, CRYPTOGAMS by <appro\@openssl.org>"
___

$code =~ s/\`([^\`]*)\`/eval $1/gem;
print $code;
close STDOUT;
