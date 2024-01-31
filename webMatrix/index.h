//HTMLCONTENT
const char *HTML_CONTENT = R"=====(
<!DOCTYPE html>
<html>
<head>
<title>Arduino R4 LED Matrix Web</title>
<meta name="viewport" content="width=device-width, initial-scale=0.7">
<style>
  body {
    font-size: 16px Arial;
    color: white;
    background-color: blue;
  }
  .user-input {
    margin-bottom: 20px;
  }
  .user-input input {
    flex: 1;
    border: 1px solid #444;
    padding: 5px;
  }
  .user-input input[type="submit"] {
    margin-left: 5px;
    background-color: #0000ff;
    color: #ffffff;
    border: none;
    padding: 5px 10px;
    cursor: pointer;
  }
</style>
</head>
<body>
    <h2>Arduino - LED Matrix via Web</h2>
  <form class="user-input" action="" method="GET">
      <input type="text" id="message" name="message" placeholder="Cell (A1-L9)">
    <input type="submit" value="Send">
    </form>
</body>
</html>
)=====";
