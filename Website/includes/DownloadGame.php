<?php
session_start();

ini_set('include_path', ini_get('include_path') . ';' . $_SERVER['DOCUMENT_ROOT'] . '/includes');
require_once 'Global.php';

$dao = new DataAccessObject();
$sql = "INSERT INTO downloads (id, data) VALUES(DEFAULT, DEFAULT)";
$params = array();

try {
  $dao->StartTransaction();
  $retOk = $dao->ExecuteNonQuery($sql, $params);
  $dao->CommitTransaction();
} catch (DatabaseException $dbe) {
  $dao->RollbackTransaction();
  throw $dbe;
}

header('Location:/DEICargo.zip');
?>
