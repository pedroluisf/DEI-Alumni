<?php
/**
 * Defines active records.
 * @author Pedro
 */
abstract class ActiveRecord {
  protected abstract function Create();
  protected abstract function Read($id);
  protected abstract function Update();
  protected abstract function Delete();
  protected abstract function Exists();
  protected abstract function GetLastInsertId(DataAccessObject $dao);
}

?>
