from __future__ import print_function as _
from __future__ import division as _
from __future__ import absolute_import as _
import logging as _logging
import json as _json

_target = 'auto'

def set_target(target='auto'):
    """
    Sets the target for visualizations launched with the `show` method. If
    unset, or if target is not provided, defaults to 'auto'.

    Notes
    -----
    - When in 'auto' target, `show` will display plot output inline when in
      Jupyter Notebook, and otherwise will open a native GUI window on macOS
      and Linux.

    Parameters
    ----------
    target : str
        The target for rendering visualizations launched with `show` methods.
        Possible values are:
        * 'auto': display plot output inline when in Jupyter Notebook, and
          otherwise launch a native GUI window.
        * 'gui': always launch a native GUI window.
    """
    global _target
    if target not in ['auto', 'gui']:
        raise ValueError("Expected target to be one of: 'auto', 'gui'.")
    _target = target


class Plot(object):
    """
    An immutable object representation of a visualization.

    Notes
    -----
    - A plot object is returned via the SFrame's or SArray's .plot() method

    Examples
    --------
    Suppose 'plt' is an Plot Object

    We can view it using:

    >>> plt.show()

    We can save it using:

    >>> plt.save('vega_spec.json')

    We can also save the vega representation of the plot without data:

    >>> plt.save('vega_spec.json', False)

    """
    def __init__(self, _proxy=None):
        if (_proxy):
            self.__proxy__ = _proxy
        else:
            self.__proxy__ = None

    def show(self):
        """
        A method for displaying the Plot object

        Notes
        -----
        - The plot will render either inline in a Jupyter Notebook, or in a
          native GUI window, depending on the value provided in
          `turicreate.visualization.set_target` (defaults to 'auto').

        Examples
        --------
        Suppose 'plt' is an Plot Object

        We can view it using:

        >>> plt.show()

        """
        global _target
        display = False
        try:
            if _target == 'auto' and \
               get_ipython().__class__.__name__ == "ZMQInteractiveShell":
                self._repr_javascript_()
                display = True
        except NameError:
            pass
        finally:
            if not display:
                import sys
                if sys.platform != 'darwin' and sys.platform != 'linux2' and sys.platform != 'linux':
                     raise NotImplementedError('Visualization is currently supported only on macOS and Linux.')

                self.__proxy__.get('call_function', {'__function_name__': 'show'})

    def save(self, filepath, include_data=True):
        """
        A method for saving the Plot object in a vega representation

        Parameters
        ----------
        include_data : bool, optional
            If True, save's the Plot in a vega spec with the data spec
            included.

        Notes
        -----
        - The save method saves the Plot object in a vega json format

        Examples
        --------
        Suppose 'plt' is an Plot Object

        We can save it using:

        >>> plt.save('vega_spec.json')

        We can also save the vega representation of the plot without data:

        >>> plt.save('vega_spec.json', False)

        """
        spec = _json.loads(self.__proxy__.get('call_function', {'__function_name__': 'get_spec'}))

        if(include_data):
            data = _json.loads(self.__proxy__.get('call_function', {'__function_name__': 'get_data'}))["data_spec"]

            for x in range(0, len(spec["vega_spec"]["data"])):
                if(spec["vega_spec"]["data"][x]["name"] == "source_2"):
                    spec["vega_spec"]["data"][x] = data
                    break;

        with open(filepath, 'w') as fp:
            _json.dump(spec, fp)

    def _get_data(self):
        return _json.loads(self.__proxy__.get('call_function', {'__function_name__': 'get_data'}))

    def _get_vega(self, include_data=True):
        if(include_data):
            spec = _json.loads(self.__proxy__.get('call_function', {'__function_name__': 'get_spec'}))
            data = _json.loads(self.__proxy__.get('call_function', {'__function_name__': 'get_data'}))["data_spec"]
            for x in range(0, len(spec["vega_spec"]["data"])):
                if(spec["vega_spec"]["data"][x]["name"] == "source_2"):
                    spec["vega_spec"]["data"][x] = data
                    break;
            return spec
        else:
            return _json.loads(self.__proxy__.get('call_function', {'__function_name__': 'get_spec'}))

    def _repr_javascript_(self):
        from IPython.core.display import display, HTML

        vega_spec = self._get_vega(True)["vega_spec"]

        vega_html = '<html lang="en"> \
                        <head> \
                            <script src="https://cdnjs.cloudflare.com/ajax/libs/vega/3.0.8/vega.js"></script> \
                            <script src="https://cdnjs.cloudflare.com/ajax/libs/vega-embed/3.0.0-rc7/vega-embed.js"></script> \
                            <script src="https://cdnjs.cloudflare.com/ajax/libs/vega-tooltip/0.5.1/vega-tooltip.min.js"></script> \
                            <link rel="stylesheet" type="text/css" href="https://cdnjs.cloudflare.com/ajax/libs/vega-tooltip/0.5.1/vega-tooltip.min.css"> \
                            <style> \
                            .vega-actions > a{ \
                                color:white; \
                                text-decoration: none; \
                                font-family: "Arial"; \
                                cursor:pointer; \
                                padding:5px; \
                                background:#AAAAAA; \
                                border-radius:4px; \
                                padding-left:10px; \
                                padding-right:10px; \
                                margin-right:5px; \
                            } \
                            .vega-actions{ \
                                margin-top:20px; \
                                text-align:center \
                            }\
                            .vega-actions > a{ \
                                background:#999999;\
                            } \
                            </style> \
                        </head> \
                        <body> \
                            <div id="vis"> \
                            </div> \
                            <script> \
                                var vega_json = '+_json.dumps(_json.dumps(vega_spec)).replace("'", "&apos;")+'; \
                                var vega_json_parsed = JSON.parse(vega_json); \
                                var toolTipOpts = { \
                                    showAllFields: true \
                                }; \
                                if(vega_json_parsed["metadata"] != null){ \
                                    if(vega_json_parsed["metadata"]["bubbleOpts"] != null){ \
                                        toolTipOpts = vega_json_parsed["metadata"]["bubbleOpts"]; \
                                    }; \
                                }; \
                                vegaEmbed("#vis", vega_json_parsed).then(function (result) { \
                                    vegaTooltip.vega(result.view, toolTipOpts);  \
                                }); \
                            </script> \
                        </body> \
                    </html>'

        display(HTML('<html> \
                <body> \
                    <iframe style="border:0;margin:0" width="'+str((vega_spec["width"] if "width" in vega_spec else 600)+200)+'" height="'+str(vega_spec["height"]+220)+'" srcdoc='+"'"+vega_html+"'"+' src="demo_iframe_srcdoc.htm"> \
                        <p>Your browser does not support iframes.</p> \
                    </iframe> \
                </body> \
            </html>'));
