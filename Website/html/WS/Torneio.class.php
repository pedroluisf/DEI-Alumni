<?php

/**
 * Description of Torneio
 *
 * @author Pedro
 */
class Torneio {

  private $Id;
  private $Nome;
  private $DataInicio;
  private $DataFim;

  public function getId() {
    return $this->Id;
  }

  public function setId($id) {
    $this->Id = $id;
  }

  public function getNome() {
    return $this->Nome;
  }

  public function setNome($nome) {
    $this->Nome = $nome;
  }

  public function getDataInicio() {
    return $this->DataInicio;
  }

  public function setDataInicio($dataInicio) {
    $this->DataInicio = $dataInicio;
  }

  public function getDataFim() {
    return $this->DataFim;
  }

  public function setDataFim($dataFim) {
    $this->DataFim = $dataFim;
  }

  public function __construct($id = 0, $nome = '', $dataInicio = null, $dataFim = null) {
    $this->Id = $id;
    $this->Nome = $nome;
    $this->DataInicio = $dataInicio;
    $this->DataFim = $dataFim;
  }

}

?>
