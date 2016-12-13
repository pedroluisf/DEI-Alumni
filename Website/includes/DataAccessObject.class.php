<?php

/**
 * Nesta classe estão implementados todos os métodos genéricos para acesso aos dados.
 *
 * @author Pedro
 */
class DataAccessObject {

  private $conn;
  private $inTransaction;

  function __construct(PDO $conn = null) {
    if ($conn == null) {
      $factory = ConnectionFactory::GetInstance();
      $this->conn = $factory->GetConnectionFromConfigFile(true);
    } else {
      $this->conn = $conn;
    }

    $this->inTransaction = false;
  }

  function __destruct() {
    if ($this->inTransaction) {
      $this->conn->rollBack();
      $this->inTransaction = false;
    }
    $this->conn = null;
  }

  public function ExecuteQuery($sql, array $params) {
    if (empty($sql))
      throw new ApplicationException("A expressão sql é vazia.");
    if (!is_array($params))
      throw new ApplicationException("Não foi passado um array de parâmetros.");

    $statement = $this->conn->prepare($sql);

    if ($statement->execute($params)) {
      return $statement->fetchAll();
    } else {
      $info = $statement->errorInfo();
      throw new DatabaseException($info[2], $info[1]);
    }

    return null;
  }

  public function ExecuteNonQuery($sql, array $params) {
    if (empty($sql))
      throw new ApplicationException("A expressão sql é vazia.");
    if (!is_array($params))
      throw new ApplicationException("Não foi passado um array de parâmetros.");

    $statement = $this->conn->prepare($sql);
    if ($statement->execute($params)) {
      return true;
    } else {
      $info = $statement->errorInfo();
      throw new DatabaseException($info[2], $info[1]);
    }

    return false;
  }
  
  public function ExecuteScalar($sql, array $params) {
    if (empty($sql))
      throw new ApplicationException("A expressão sql é vazia.");
    if (!is_array($params))
      throw new ApplicationException("Não foi passado um array de parâmetros.");

    $statement = $this->conn->prepare($sql);

    if ($statement->execute($params)) {
      return $statement->fetchColumn(0);
    } else {
      $info = $statement->errorInfo();
      throw new DatabaseException($info[2], $info[1]);
    }

    return null;
  }  

  public function StartTransaction() {
    if ($this->conn != null && !$this->inTransaction) {
      if ($this->conn->beginTransaction()) {
        $this->inTransaction = true;
        return true;
      }
    }

    return false;
  }

  public function CommitTransaction() {
    if ($this->conn != null && $this->inTransaction) {
      if ($this->conn->commit()) {
        $this->inTransaction = false;
        return true;
      }
    }

    return false;
  }

  public function RollbackTransaction() {
    if ($this->conn != null && $this->inTransaction) {
      if ($this->conn->rollBack()) {
        $this->inTransaction = false;
        return true;
      }
    }

    return false;
  }

  public function IsInTransaction() {
    return $this->inTransaction;
  }
}

?>
