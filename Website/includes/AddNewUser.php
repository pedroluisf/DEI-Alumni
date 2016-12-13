<?php
session_start();

ini_set('include_path', ini_get('include_path') . ';' . $_SERVER['DOCUMENT_ROOT'] . '/includes');
require_once 'Global.php';

if (
        isset($_REQUEST['name']) &&
        isset($_REQUEST['username']) &&
        isset($_REQUEST['email'])
   ) 
{
  
  $name = $_REQUEST['name'];
  $username = $_REQUEST['username'];
  $password = $_REQUEST['password'];
  $email = $_REQUEST['email'];
  
  try {
    $u = new Utilizador($name, $email, $username, $password);
    // seria necessário verificar se o utilizador existe antes de o introduzir
	$u->Save();
    
    $_SESSION['DEI_msg'] = 'Utilizador registado com sucesso!';
	$_SESSION['DEI_user'] = $username;
	
    header('Location:/index.php');
  } catch (Exception $exc) {
    die($exc->getMessage());
  }

  
}
?>
