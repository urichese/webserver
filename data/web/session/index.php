<?php
session_start();

if (isset($_GET['del_color']) && $_GET['del_color'] == 'y')
	unset($_SESSION['new_color']);

if (isset($_GET['del'])&& $_GET['del'] == 'y')
	session_unset();

if (isset($_POST['User_name']) && $_POST['User_name'] != '')
	$_SESSION['User_name'] = $_POST['User_name'];

if (!isset($_SESSION['User_name']))
{
?>
<h1>Привет гость</h1>
<form method="post" enctype="multipart/form-data" action="/session/index.php">
	<input type="text" name="User_name">
	<button type="submit">Войти</button>
</form>
<?php
}
else
{
?>
<script>
	function set_color(event)
	{
		var xhr = new XMLHttpRequest();
		xhr.open('POST', '/session/set_color.php', false);
		xhr.setRequestHeader('Content-type', 'application/x-www-form-urlencoded; charset=utf-8');
		xhr.send("new_color="+event.target.value);
	}
</script>
<h1>Привет <?php echo$_SESSION['User_name'];?></h1>
	<input name="Color Picker" style="width: 200px;height: 200px;" oninput="set_color(event);" type="color"
	<?php echo((!isset($_SESSION['new_color'])) ? "" :  'value="'.$_SESSION['new_color'].'"');?>
	/><br><br>
	<button type="submit" onclick="return location.href = '/session/index.php?del_color=y'" >Забыть цвет</button>
	<button type="submit" onclick="return location.href = '/session/index.php?del=y'" >Забыть всё</button>
<?php
}
?>
