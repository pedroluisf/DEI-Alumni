<?php

session_start();
ini_set('include_path', ini_get('include_path') . ';' . $_SERVER['DOCUMENT_ROOT'] . '/includes');
require_once 'Global.php';

if (
        isset($_REQUEST['nome']) &&
        isset($_REQUEST['data_inicio']) &&
        isset($_REQUEST['data_fim']) &&
        isset($_REQUEST['min_jogadores']) &&
        isset($_REQUEST['max_jogadores'])
) {

  $nome = $_REQUEST['nome'];
  $datai = $_REQUEST['data_inicio'];
  $dataf = $_REQUEST['data_fim'];
  $minj = $_REQUEST['min_jogadores'];
  $maxj = $_REQUEST['max_jogadores'];

  try {
    $dao = new DataAccessObject();
    $sql = "INSERT INTO Torneios(id, nome, data_inicio, data_fim, min_jogadores, max_jogadores) VALUES(DEFAULT, :nome, :data_inicio, :data_fim, :min_jogadores, :max_jogadores)";
    $params = array(
        ':nome' => $nome, 
        ':data_inicio' => $datai, 
        ':data_fim' => $dataf, 
        ':min_jogadores' => $minj, 
        ':max_jogadores' => $maxj
    );

    $dao->StartTransaction();
    $dao->ExecuteNonQuery($sql, $params);
    $dao->CommitTransaction();      
  } catch (DatabaseException $dbe) {
    $dao->RollbackTransaction();
    throw $dbe;
  } catch (Exception $exc) {
    //die($exc->getMessage());
    // should log the error
  }
}
?>