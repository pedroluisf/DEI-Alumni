<?php

/**
 * Description of Classificacao
 *
 * @author Pedro
 */
class Classificacao {

  private $Posicao;
  private $Nome;
  private $Pontuacao;

  public function getPosicao() {
    return $this->Posicao;
  }

  public function setPosicao($posicao) {
    $this->Posicao = $posicao;
  }

  public function getNome() {
    return $this->Nome;
  }

  public function setNome($nome) {
    $this->Nome = $nome;
  }

  public function getPontuacao() {
    return $this->Pontuacao;
  }

  public function setPontuacao($pontuacao) {
    $this->Pontuacao = $pontuacao;
  }

  public function __construct($posicao = 0, $nome = '', $pontuacao = 0) {
    $this->Posicao = $posicao;
    $this->Nome = $nome;
    $this->Pontuacao = $pontuacao;
  }

}

?>
