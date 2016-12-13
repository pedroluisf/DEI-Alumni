<?php

require_once 'Classificacao.class.php';
require_once 'Torneio.class.php';
require_once '../../includes/Logger.class.php';
require_once '../../includes/Global.php';

// setResultados($utilizador, $mapa, $torneio, $pontuacao)
function setResultados($args) {  
  $params = get_object_vars($args);

  $utilizador = $params['utilizador'];
  $mapa = $params['mapa'];
  $torneio = $params['torneio'];
  $pontuacao = $params['pontuacao'];
  $data = new DateTime();

  try {
    $dao = new DataAccessObject();
    $dao->StartTransaction();

    $rankingSql = "select (SELECT Count(*) FROM jogos where mapa = :mapa) - (select count(*) from jogos where mapa = :mapa and pontuacao < :pontuacao) + 1 as posicao";
    $rankingParams = array(
        ':mapa' => $mapa,
        ':pontuacao' => $pontuacao
    );
    $ranking = $dao->ExecuteScalar($rankingSql, $rankingParams);

    $historicoSql = "INSERT INTO historico(id, ranking) VALUES(DEFAULT, :ranking)";
    $historicoParams = array(
        ':ranking' => $ranking
    );
    $dao->ExecuteNonQuery($historicoSql, $historicoParams);
    $historico = $dao->ExecuteScalar("SELECT id FROM historico ORDER BY id DESC LIMIT 0, 1", array());

    $jogoSql = "INSERT INTO jogos(id, utilizador, mapa, historico, torneio, pontuacao, data) VALUES(DEFAULT, :utilizador, :mapa, :historico, :torneio, :pontuacao, :data)";
    $jogoParams = array(
        ':utilizador' => $utilizador,
        ':mapa' => $mapa,
        ':historico' => $historico,
        ':torneio' => $torneio,
        ':pontuacao' => $pontuacao,
        ':data' => $data->format('Y-m-d')
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
  
  $classificacao = array(
      new Classificacao(1, 'Magueija', 1000.99),
      new Classificacao(2, "Elvis Presley", 900.99),
      new Classificacao(3, "Bon Jovi", 800.99),
      new Classificacao(4, "Michael Jackson", 700.99),
      new Classificacao(5, "Frank Sinatra", 673.99)
  );
  return array('setResultadosResult' => array('Classificacao' => $classificacao));
}

// getTorneio($utilizador, $mapa)
function getTorneio($args) {
  $params = get_object_vars($args);
  $torneios = array();
  $today = new DateTime();
  $sql = "select t.nome as nome, t.data_inicio as inicio, t.data_fim as fim from torneios t inner join inscricoes i on i.torneio = t.id and i.utilizador = :utilizador";

  $utilizador = $params['utilizador'];
  $mapa = $params['mapa'];
  
  try {
    $dao = new DataAccessObject();
    $rows = $dao->ExecuteQuery($sql, array(':utilizador' => $utilizador));
    
    $i = 1;
    foreach($rows as $row) {
      $inicio = $today->createFromFormat('Y-m-d', $row['inicio']);
      $fim = $today->createFromFormat('Y-m-d', $row['fim']);
      $torneios[] = new Torneio($i, $row['nome'], $inicio->format(DateTime::W3C), $fim->format(DateTime::W3C));
      $i += 1;
    }
    
  } catch (DatabaseException $dbe) {
    $dao->RollbackTransaction();
    throw $dbe;
  } catch (Exception $exc) {
    //die($exc->getMessage());
    // should log the error
  }  
  
  
//  $torneios = array(
//      new Torneio(1, 'Norte', $today->format(DateTime::W3C), $today->format(DateTime::W3C)),
//      new Torneio(2, 'Interior', $today->format(DateTime::W3C), $today->format(DateTime::W3C)),
//      new Torneio(3, 'Sul', $today->format(DateTime::W3C), $today->format(DateTime::W3C))
//  );

  return array('getTorneioResult' => array('Torneio' => $torneios));
}

// login(utilizador, md5password);
function login($args) {
  $params = get_object_vars($args);
  return array('loginResult' => $params['utilizador']);
}

$server = new SoapServer("WsAPI.wsdl");

$server->addFunction('setResultados');
$server->addFunction('getTorneio');
$server->addFunction('login');
$server->handle();