from mod_python import util

html_form = """
<!DOCTYPE html>

<html>

<head>
    <title>Dynamic form test</title>
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
    <script>
    function changeAInputValue()
    {
        var index = parseInt(document.getElementById("_index").value) + 1;
        document.getElementById("_index").value = index;
        document.getElementById("_form").submit();
    }
    </script>
</head>

<body>
    <form id="_form" action="/python/form.py/index" method="get">
        <input type="text" name="text" value="%s"><br/>
        <input type="text" name="name" value="%s"><br/>
        <input id = "_index" type="text" name="index" value="%d"><br/>

        <br/><br/><br/>
        <button type="button" onclick="changeAInputValue()">Try it</button><br/>
    </form>
</body>

</html>
"""

def index(req):

    argv = util.FieldStorage(req);
    text = argv["text"].value
    name = argv["name"].value
    index = int(argv["index"].value)

    return html_form % (text, name, index)
