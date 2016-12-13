<?php

/**
 * Description of Utilizador
 *
 * @author Pedro
 */
class Utilizador extends UtilizadorAR {

  public function getId() {
    return $this->id;
  }

  public function setId($id) {
    $this->id = $id;
  }

  public function getNome() {
    return $this->nome;
  }

  public function setNome($nome) {
    $this->nome = $nome;
  }

  public function getEmail() {
    return $this->email;
  }

  public function setEmail($email) {
    $this->email = $email;
  }
  
  public function getUsername() {
    return $this->username;
  }

  public function setUsername($username) {
    $this->username = $username;
  }

  public function getPassword() {
    return $this->password;
  }

  public function setPassword($password) {
    $this->password = md5($password);
  }
  
  function __construct($nome = '', $email = '', $username = '', $password = '') {
    $this->setNome($nome);
    $this->setEmail($email);
    $this->setUsername($username);
    $this->setPassword($password);
    parent::__construct();
  }

  public function Save() {
    
 if($this->getNome() == '') throw new ApplicationException('Nome obrigatório');
 if($this->getUsername() == '') throw new ApplicationException('Username obrigatório');
 if($this->getEmail() == '') throw new ApplicationException('Email obrigatório');
 if($this->getPassword() == '') throw new ApplicationException('Password obrigatório');
    
  if (parent::Exists()) {
      parent::Update();
    } else {
      parent::Create();
    }
  }

  public function Remove() {
    if (parent::Exists()) {
      parent::Delete();
    }
  }

  public function Load($id) {
    if ($id <= 0)
      throw new ApplicationException('O id fornecido é inválido. Apenas são aceites valores maiores que 0.');

    parent::Read($id);
  }
  
}

?>
