<?php

session_start();
ini_set('include_path', ini_get('include_path') . ';' . $_SERVER['DOCUMENT_ROOT'] . '/includes');
require_once 'Global.php';

if (
        isset($_REQUEST['utilizador']) &&
        isset($_REQUEST['mapa']) &&
        isset($_REQUEST['torneio']) &&
        isset($_REQUEST['pontuacao']) &&
        isset($_REQUEST['data'])
) {

  $utilizador = $_REQUEST['utilizador'];
  $mapa = $_REQUEST['mapa'];
  $pontuacao = $_REQUEST['pontuacao'];
  $torneio = $_REQUEST['torneio'];
  $data = $_REQUEST['data'];

  try {
    $dao = new DataAccessObject();
    $dao->StartTransaction();

    $rankingSql = "select (SELECT Count(*) FROM jogos where mapa = :mapa) - (select count(*) from jogos where mapa = :mapa and pontuacao < :pontuacao) + 1 as posicao";
    $rankingParams = array(
        ':mapa' => $mapa,
        ':pontuacao' => $pontuacao
    );
    $ranking = $dao->ExecuteScalar($rankingSql, $rankingParams);

    $historicoSql = "INSERT INTO Historico(id, ranking) VALUES(DEFAULT, :ranking)";
    $historicoParams = array(
        ':ranking' => $ranking
    );
    $dao->ExecuteNonQuery($historicoSql, $historicoParams);

    $jogoSql = "INSERT INTO Jogos(id, utilizador, mapa, historico, torneio, pontuacao, data) VALUES(DEFAULT, :utilizador, :mapa, :historico, :torneio, :pontuacao, :data)";
    $jogoParams = array(
        ':utilizador' => $utilizador,
        ':mapa' => $mapa,
        ':historico' => $historico,
        ':torneio' => $torneio,
        ':pontuacao' => $pontuacao,
        ':data' => $data
    );
    $dao->ExecuteNonQuery($jogoSql, $jogoParams);

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
