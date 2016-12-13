<?php

/**
 * Description of UtilizadorAR
 *
 * @author Pedro
 */
class UtilizadorAR extends ActiveRecord {

  protected $id;
  protected $nome;
  protected $username;
  protected $password;
  protected $email;
      
  function __construct() {
    ;
  }

  protected final function Create() {
    $retOk = false;
    $dao = new DataAccessObject();
    $sql = "INSERT INTO utilizadores(Id, Nome, Email, Username, Password) VALUES(DEFAULT, :Nome, :Email, :Username, :Password)";
    $params = array(
        ':Nome' => $this->nome,
        ':Email' => $this->email,
        ':Username' => $this->username,
        ':Password' => $this->password
    );

    try {

      $dao->StartTransaction();
      $retOk = $dao->ExecuteNonQuery($sql, $params);
      $this->id = $this->GetLastInsertId($dao);
      $dao->CommitTransaction();
    } catch (DatabaseException $dbe) {

      $dao->RollbackTransaction();
      throw $dbe;
    }

    return $retOk;
  }

  protected final function Delete() {
    $retOk = false;
    $dao = new DataAccessObject();
    $sql = "DELETE FROM utilizadores WHERE Id = :Id";
    $params = array(
        ':Id' => $this->id
    );

    $retOk = $dao->ExecuteNonQuery($sql, $params);

    return $retOk;
  }

  protected final function Exists() {
    $retVal = 0;
    $dao = new DataAccessObject();
    $sql = "SELECT Count(*) AS n FROM utilizadores WHERE Id = :Id";
    $params = array(
        ':Id' => $this->id
    );

    $retVal = $dao->ExecuteScalar($sql, $params);

    return $retVal > 0;
  }

  protected final function GetLastInsertId(DataAccessObject $dao) {
    if ($dao == null)
      throw new ApplicationException('O objecto de acesso à base de dados não pode ser nulo.');

    $retVal = 0;
    $sql = "SELECT Max(Id) AS Id FROM utilizadores";
    $params = array();

    try {
      $retVal = $dao->ExecuteScalar($sql, $params);
    } catch (DatabaseException $dbe) {
      throw $dbe;
    }

    return $retVal;
  }

  protected final function Read($id) {
    $dao = new DataAccessObject();
    $sql = "SELECT * FROM utilizadores WHERE Id = :Id";
    $params = array(
        'Id' => $id
    );

    $rows = $dao->ExecuteQuery($sql, $params);
    $this->id = $rows[0]['Id'];
    $this->nome = $rows[0]['Nome'];
    $this->email = $rows[0]['Email'];
  }

  protected final function Update() {
    $retOk = false;
    $dao = new DataAccessObject();
    $sql = "UPDATE utilizadores SET Nome = :Nome, Email = :Email WHERE Id = :Id";
    $params = array(
        ':Nome' => $this->nome,
        ':Email' => $this->email,
        ':Id' => $this->id
    );

    $retOk = $dao->ExecuteNonQuery($sql, $params);

    return $retOk;
  }

  public static function FindByNome($nome) {
    $dao = new DataAccessObject();
    $sql = "SELECT * FROM utilizadores WHERE Nome = :Nome";
    $params = array(
        'Nome' => $nome
    );

    $rows = $dao->ExecuteQuery($sql, $params);

    if ($rows != null) {
      $u = new Utilizador();

      $u->id = $rows[0]['Id'];
      $u->nome = $rows[0]['Nome'];
      $u->email = $rows[0]['Email'];

      return $u;
    }

    return null;
  }

  public final function validaUtilizadorByPassword() {
    $retVal = 0;
    $dao = new DataAccessObject();
    $sql = "SELECT Count(*) AS n FROM utilizadores WHERE Username = :User AND Password = :Pass";
    $params = array(
        ':User' => $this->username,
		':Pass' => $this->password
    );

    $retVal = $dao->ExecuteScalar($sql, $params);

    return $retVal > 0;
  }

}

?>
