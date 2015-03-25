#define EDITPAGE "<!DOCTYPE html>" \
"<html lang=\"en\">" \
"<head>" \
"<meta charset=\"utf-8\">" \
"<meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">" \
"<title>mbed mruby editor</title>" \
"<link href=\"https://cdnjs.cloudflare.com/ajax/libs/codemirror/5.0.0/codemirror.min.css\" rel=\"stylesheet\" type=\"text/css\">" \
"<link href=\"https://cdnjs.cloudflare.com/ajax/libs/codemirror/5.0.0/theme/solarized.min.css\" rel=\"stylesheet\" type=\"text/css\">" \
"<link href=\"http://fonts.googleapis.com/css?family=Source+Code+Pro\" rel=\"stylesheet\" type=\"text/css\">" \
"<style>" \
"textarea{font-family: 'Source Code Pro', sans-serif;}" \
"h2{color: #333;}" \
"#nav-bar{height: 30px;}" \
"#header{height: 2.5em;}" \
"#editor{height: 500px; width: 100%;}" \
"</style>" \
"</head>" \
"<body>" \
"<div id=\"header\">" \
"<h2>mbed mruby editor</h2>" \
"</div>" \
"<div id=\"nav-bar\">" \
"<button id=\"run-btn\">Run</button>" \
"</div>" \
"<div id=\"editor-container\">" \
"<textarea id=\"editor\">include Mbed\n" \
"led = DigitalOut.new LED1\n" \
"sleep 1\n" \
"led.write 1\n" \
"sleep 1\n" \
"led.write 0\n" \
"sleep 1\n" \
"led.write 1</textarea>\n" \
"</div>\n" \
"<script src=\"https://ajax.googleapis.com/ajax/libs/jquery/1.11.2/jquery.min.js\"></script>" \
"<script src=\"https://cdnjs.cloudflare.com/ajax/libs/codemirror/5.0.0/codemirror.min.js\" type=\"text/javascript\" charset=\"utf-8\"></script>" \
"<script src=\"https://cdnjs.cloudflare.com/ajax/libs/codemirror/5.0.0/mode/ruby/ruby.min.js\" type=\"text/javascript\" charset=\"utf-8\"></script>" \
"<script>" \
"var editor = CodeMirror.fromTextArea(document.getElementById(\"editor\"), {" \
"    lineNumbers: true," \
"    mode: \"ruby\"," \
"    theme: \"solarized light\"" \
"});" \
"$('#run-btn').click(function() {" \
"    var code = editor.getValue();" \
"    $.ajax({" \
"        url: 'run'," \
"        type: 'POST'," \
"        data: code," \
"        contentType: 'text/plain'," \
"        success: function() {" \
"        }," \
"        error: function() {" \
"        }" \
"    });" \
"});" \
"</script>" \
"</body>" \
"</html>"
