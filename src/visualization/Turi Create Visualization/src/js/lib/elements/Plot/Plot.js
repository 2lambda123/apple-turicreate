import React, { Component } from 'react';
import vegaEmbed from 'vega-embed';
import {vega as vegaTooltip} from'vega-tooltip';
import './Plot.css';

var vega = require('vega');

window.vega_type = vega;

class TcPlot extends Component {

    componentDidMount(){
        this.addSpec(this.props.vega_spec);
    }

    checkLoadedFlag(data, $this) {
        if($this.vegaLoading) {
            window.setTimeout($this.checkLoadedFlag, 100, data, $this);
        } else {
            if($this.vegaLoading){
                debugger;
            }

            if (!data || !data.values) {
                debugger;
            }

            var newData = data.values.slice();

            var changeSet = vega.changeset();

            if(data.progress != null){
                var progress = parseFloat(data.progress);
                if(parseInt(progress*100, 10) >= 100){
                    document.getElementById('progress_bar').style.width = parseInt(progress*100)+"%";
                    setTimeout(function(){
                               document.getElementById('progress_bar').style.opacity = "0.0";
                               }, 1000);
                }else{
                    document.getElementById('progress_bar').style.width = parseInt(progress*100)+"%";
                }
            }

            var prevData = $this.vegaView.data("source_2");

            for(var y = 0; y < newData.length; y++ ){
                if(newData[y]["a"] != null){
                    for(var x = 0; x < prevData.length; x++ ){
                        if(prevData[x]["a"] === newData[y]["a"]){
                            changeSet = changeSet.remove(prevData[x]);
                        }
                    }
                }else{
                    if(prevData.length > 0){
                        changeSet = changeSet.remove(prevData);
                        break;
                    }
                }
            }

            changeSet = changeSet.insert(newData);
            $this.vega_container.classList.remove("uninitialized");
            $this.vegaView.change("source_2", changeSet).runAfter(function(viewInstance) {

                                                                  });

            $this.vegaView.toCanvas().then(function(result){
                                           $this.hidden_container.innerHTML = '';
                                           $this.hidden_container.appendChild(result);
                                           });
        }
    }

    updateData(data){
        this.checkLoadedFlag(data, this);
    }

    addSpec(spec){
        this.bubbleOpts = {
        showAllFields: true,
        };

        this.vega_json = spec;

        this.opt = {
        mode: ('$schema' in this.vega_json && this.vega_json['$schema'].indexOf('vega-lite') === -1) ? "vega": "vega-lite",
        renderer: "svg"
        };

        this.vega_json.autosize = {"type": "pad", "resize": true, "contains": "padding"};

        if(this.vega_json["metadata"] != null){
            if(this.vega_json["metadata"]["bubbleOpts"] != null){
                this.bubbleOpts = this.vega_json["metadata"]["bubbleOpts"];
            }
        }

        this.vegaLoading = true;

        var $this = this;

        vegaEmbed(this.vega_container, this.vega_json, this.opt).then(function(viewInstance) {
          $this.vegaView = viewInstance.view;

          vegaTooltip($this.vegaView, $this.vega_json, $this.bubbleOpts);
          $this.vegaResult = viewInstance.spec;
          $this.vegaLoading = false;

          if(window.navigator.platform === 'MacIntel'){
            window.webkit.messageHandlers["scriptHandler"].postMessage({status: 'ready'});
          }

        }).catch(function(error) {
          console.error(error);
        });
    }

    getSpec(){
        var previousData = this.vegaView.data("source_2");

        for(var x = 0; x < this.vegaResult.data.length; x++){
            if(this.vegaResult.data[x]["name"] === "source_2"){
                this.vegaResult.data[x]["values"] = previousData;
            }
        }

        return JSON.stringify(this.vegaResult);
    }

    getData(){
        var previousData = this.vegaView.data("source_2");

        var array = typeof previousData != 'object' ? JSON.parse(previousData) : previousData;
        var str = '';

        for (var i = 0; i < array.length; i++) {
            var line = '';
            for (var index in array[i]) {
                if (line != '') line += ','

                    line += array[i][index];
            }

            str += line + '\r\n';
        }

        return str;
    }

    exportPNG(){
        return this.hidden_container.childNodes[0].toDataURL("image/png").replace(/^data:image\/(png|jpg);base64,/, "");
    }

    render() {
        return (
                <div>
                <div className={["vega_container", "uninitialized"].join(' ')} ref={(vega_container) => { this.vega_container = vega_container; }}>
                </div>
                <div className={["hidden_cont"].join(' ')} ref={(hidden_container) => { this.hidden_container = hidden_container; }}>
                </div>
                </div>
                );
    }
}

export default TcPlot;
