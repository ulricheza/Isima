<html>
    <head>
        <link rel="stylesheet" href="http://twitter.github.com/bootstrap/1.4.0/bootstrap.min.css">
        <style type="text/css">
            .container {
                margin-top: 40px;
            }
            .container h1 {
                margin-bottom: 40px;
            }
            .exception {
                font-size: 11px;
                font-family: Courier New, Courier, monospace;
            }
        </style>
    </head>
    <body style="text-align: center">
        <div class="container">
            <h1>Ooops! Something went wrong :'(</h1>

            <div class="alert-message error">
                <p>${requestScope.error}</p>
            </div>
        </div>
    </body>
</html>