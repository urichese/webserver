<?php
if (isset($_POST['new_color']))
{
	session_start();
	$_SESSION['new_color'] = $_POST['new_color'];
}
else
	http_response_code(404);
?>