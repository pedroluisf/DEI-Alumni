<?php
session_start();
ini_set('include_path', ini_get('include_path') . ';' . $_SERVER['DOCUMENT_ROOT'] . '/includes');
require_once 'Global.php';

if (
        isset($_REQUEST['p1']) &&
        isset($_REQUEST['p2'])
   ) 
{
  
  $username = $_REQUEST['p1'];
  $password = $_REQUEST['p2'];
    
  try {
    $u = new Utilizador("", "", $username, $password);
    $valido = $u->validaUtilizadorByPassword();
    if ($valido) {
    	$_SESSION['DEI_msg'] = 'Utilizador válido!';
		$_SESSION['DEI_user'] = $username;
    	header('Location:/index.php');
	} else {
		$_SESSION['DEI_msg'] = 'Utilizador inválido!';
		unset($_SESSION['DEI_user']);
    	header('Location:/login.php');
	}
  } catch (Exception $exc) {
    die($exc->getMessage());
  }

  
}
?>
