<form method="post" enctype="multipart/form-data" action="http://localhost:8080/php_test.php?a=ббб&b&c=&d=4&test=ааа">
	<input type="text" name="test">
	<input type="text" name="test2">
	<input type="file" name="photo" multiple>
	<button type="submit">Отправить</button>
</form>
<br>
<?php
setcookie("TestCookie", "Test", time()+3600);
echo "Hello\n";
var_dump($_GET);
var_dump($_POST);
var_dump($_FILES);
var_dump($_COOKIE);

session_start();
// initialize session variables
echo "SESSION_ID - ".session_id();
?>
