<?php

session_start();
ini_set('include_path', ini_get('include_path') . ';' . $_SERVER['DOCUMENT_ROOT'] . '/includes');
require_once 'Global.php';

if (
        isset($_REQUEST['nome']) &&
        isset($_REQUEST['downloads']) &&
        isset($_REQUEST['mapa'])
) {

  $utilizador = $_REQUEST['nome'];
  $mapa = $_REQUEST['downloads'];
  $historico = $_REQUEST['mapa'];

  try {
    $dao = new DataAccessObject();
    $sql = "INSERT INTO Mapas(id, nome, downloads, mapa) VALUES(DEFAULT, :nome, :downloads, :mapa, :torneio, :pontuacao, :data)";
    $params = array(
        ':utilizador' => $utilizador,
        ':mapa' => $mapa,
        ':historico' => $historico,
        ':torneio' => $torneio,
        ':pontuacao' => $pontuacao,
        ':data' => $data
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
