<?php
session_start();

ini_set('include_path', ini_get('include_path') . ':../includes');

if (isset($_GET['action'])){
	$action = $_GET['action'];
	switch ($action){
		case 'login':
		  require_once 'LoginUser.php';
		  break;
		case 'register':
		  require_once 'AddNewUser.php';
		  break;
		case 'download':
		  require_once 'DownloadGame.php';
		  break;		  
		  
		  
		default:
		  die("Acção inválida!!!");
		  break;
	}
}else {
	die("Acção inválida!!!");
}
  
?>
