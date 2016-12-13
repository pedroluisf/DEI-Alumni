<?php

/**
 * Description of ConnectionFactory
 *
 * @author Pedro
 */
class ConnectionFactory {

  private static $instance;

  private function __construct() {
    ;
  }

  public static function GetInstance() {
    if (self::$instance == null) {
      $className = __CLASS__;
      self::$instance = new self();
    }

    return self::$instance;
  }

  public function GetConnection($dsn, $username, $passwd, $persistent = false) {
    $pdo = null;

    try {
      $pdo = new PDO($dsn, $username, $passwd, array(PDO::ATTR_PERSISTENT => $persistent));
    } catch (Exception $exc) {
      Logger::logException($exc);
      throw new ApplicationException('Não foi possível criar a ligação. Por favor, consulte o log.');
    }

    return $pdo;
  }

  public function GetConnectionFromConfigFile($configFileName = '', $persistent = false) {
    $fileName = 'Config.php';
    $pdo = null;

    if (!empty($configFileName) && file_exists($configFileName)) {
      $fileName = $configFileName;
    }

    require_once $fileName;
    if (defined('DSN') && defined('USERNAME') && defined('PASSWD')) {
      try {
        $pdo = new PDO(DSN, USERNAME, PASSWD, array(PDO::ATTR_PERSISTENT => $persistent));
      } catch (Exception $exc) {
        Logger::logException($exc);
        throw new ApplicationException('Não foi possível criar a ligação. Por favor, consulte o log.');
      }
    }

    return $pdo;
  }

}

?>
