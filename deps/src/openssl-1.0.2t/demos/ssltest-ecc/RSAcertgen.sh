#!/bin/sh

# For a list of supported curves, use "apps/openssl ecparam -list_curves".

# Path to the openssl distribution
OPENSSL_DIR=../..
# Path to the openssl program
OPENSSL_CMD=$OPENSSL_DIR/apps/openssl
# Option to find configuration file
OPENSSL_CNF="-config $OPENSSL_DIR/apps/openssl.cnf"
# Directory where certificates are stored
CERTS_DIR=./Certs
# Directory where private key files are stored
KEYS_DIR=$CERTS_DIR
# Directory where combo files (containing a certificate and corresponding
# private key together) are stored
COMBO_DIR=$CERTS_DIR
# cat command
CAT=/bin/cat
# rm command
RM=/bin/rm
# mkdir command
MKDIR=/bin/mkdir
# The certificate will expire these many days after the issue date.
DAYS=1500
TEST_CA_FILE=rsa1024TestCA
TEST_CA_DN="/C=US/ST=CA/L=Mountain View/O=Sun Microsystems, Inc./OU=Sun Microsystems Laboratories/CN=Test CA (1024 bit RSA)"

TEST_SERVER_FILE=rsa1024TestServer
TEST_SERVER_DN="/C=US/ST=CA/L=Mountain View/O=Sun Microsystems, Inc./OU=Sun Microsystems Laboratories/CN=Test Server (1024 bit RSA)"

TEST_CLIENT_FILE=rsa1024TestClient
TEST_CLIENT_DN="/C=US/ST=CA/L=Mountain View/O=Sun Microsystems, Inc./OU=Sun Microsystems Laboratories/CN=Test Client (1024 bit RSA)"

# Generating an EC certificate involves the following main steps
# 1. Generating curve parameters (if needed)
# 2. Generating a certificate request
# 3. Signing the certificate request
# 4. [Optional] One can combine the cert and private key into a single
#    file and also delete the certificate request

$MKDIR -p $CERTS_DIR
$MKDIR -p $KEYS_DIR
$MKDIR -p $COMBO_DIR

echo "Generating self-signed CA certificate (RSA)"
echo "==========================================="

$OPENSSL_CMD req $OPENSSL_CNF -nodes -subj "$TEST_CA_DN" \
    -keyout $KEYS_DIR/$TEST_CA_FILE.key.pem \
    -newkey rsa:1024 -new \
    -out $CERTS_DIR/$TEST_CA_FILE.req.pem

$OPENSSL_CMD x509 -req -days $DAYS \
    -in $CERTS_DIR/$TEST_CA_FILE.req.pem \
    -extfile $OPENSSL_DIR/apps/openssl.cnf \
    -extensions v3_ca \
    -signkey $KEYS_DIR/$TEST_CA_FILE.key.pem \
    -out $CERTS_DIR/$TEST_CA_FILE.cert.pem

# Display the certificate
$OPENSSL_CMD x509 -in $CERTS_DIR/$TEST_CA_FILE.cert.pem -text

# Place the certificate and key in a common file
$OPENSSL_CMD x509 -in $CERTS_DIR/$TEST_CA_FILE.cert.pem -issuer -subject \
	 > $COMBO_DIR/$TEST_CA_FILE.pem
$CAT $KEYS_DIR/$TEST_CA_FILE.key.pem >> $COMBO_DIR/$TEST_CA_FILE.pem

# Remove the cert request file (no longer needed)
$RM $CERTS_DIR/$TEST_CA_FILE.req.pem

echo "GENERATING A TEST SERVER CERTIFICATE (RSA)"
echo "=========================================="

$OPENSSL_CMD req $OPENSSL_CNF -nodes -subj "$TEST_SERVER_DN" \
    -keyout $KEYS_DIR/$TEST_SERVER_FILE.key.pem \
    -newkey rsa:1024 -new \
    -out $CERTS_DIR/$TEST_SERVER_FILE.req.pem

$OPENSSL_CMD x509 -req -days $DAYS \
    -in $CERTS_DIR/$TEST_SERVER_FILE.req.pem \
    -CA $CERTS_DIR/$TEST_CA_FILE.cert.pem \
    -CAkey $KEYS_DIR/$TEST_CA_FILE.key.pem \
    -out $CERTS_DIR/$TEST_SERVER_FILE.cert.pem -CAcreateserial

# Display the certificate
$OPENSSL_CMD x509 -in $CERTS_DIR/$TEST_SERVER_FILE.cert.pem -text

# Place the certificate and key in a common file
$OPENSSL_CMD x509 -in $CERTS_DIR/$TEST_SERVER_FILE.cert.pem -issuer -subject \
	 > $COMBO_DIR/$TEST_SERVER_FILE.pem
$CAT $KEYS_DIR/$TEST_SERVER_FILE.key.pem >> $COMBO_DIR/$TEST_SERVER_FILE.pem

# Remove the cert request file (no longer needed)
$RM $CERTS_DIR/$TEST_SERVER_FILE.req.pem

echo "GENERATING A TEST CLIENT CERTIFICATE (RSA)"
echo "=========================================="

$OPENSSL_CMD req $OPENSSL_CNF -nodes -subj "$TEST_CLIENT_DN" \
	     -keyout $KEYS_DIR/$TEST_CLIENT_FILE.key.pem \
	     -newkey rsa:1024 -new \
	     -out $CERTS_DIR/$TEST_CLIENT_FILE.req.pem

$OPENSSL_CMD x509 -req -days $DAYS \
    -in $CERTS_DIR/$TEST_CLIENT_FILE.req.pem \
    -CA $CERTS_DIR/$TEST_CA_FILE.cert.pem \
    -CAkey $KEYS_DIR/$TEST_CA_FILE.key.pem \
    -out $CERTS_DIR/$TEST_CLIENT_FILE.cert.pem -CAcreateserial

# Display the certificate
$OPENSSL_CMD x509 -in $CERTS_DIR/$TEST_CLIENT_FILE.cert.pem -text

# Place the certificate and key in a common file
$OPENSSL_CMD x509 -in $CERTS_DIR/$TEST_CLIENT_FILE.cert.pem -issuer -subject \
	 > $COMBO_DIR/$TEST_CLIENT_FILE.pem
$CAT $KEYS_DIR/$TEST_CLIENT_FILE.key.pem >> $COMBO_DIR/$TEST_CLIENT_FILE.pem

# Remove the cert request file (no longer needed)
$RM $CERTS_DIR/$TEST_CLIENT_FILE.req.pem
