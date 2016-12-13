<?php
/**
 * Master front page for the website.
 * @version
 * @author pedro
 */
class Page {

  /**
   * Holds the template for this page.
   * @var String
   */
  private $_template;

  /**
   * Page title.
   * @var String
   */
  private $_title;

  /**
   * Buffered page.
   * @var String
   */
  private $_page;

  /**
   * Custom page head.
   * @var String
   */
  private $_customHead;

  /**
   * Page language.
   * @var String
   */
  private $_lang;

  /**
   * Active Menu.
   * @var int
   */
  private $_active_menu;

  /**
   * Creates a new instance of AdminMasterPage.
   * @param String $title The title for the page.
   */
  public function __construct($template, $title, $lang) {
    $this->_template = $template;
    $this->_title = $title;
    $this->_lang = $lang;
    $this->_customHead = "";
	$this->_active_menu = 0;

    // se mais algum directorio for necessario incluir aqui
    ini_set('include_path', ini_get('include_path') . ':' . $_SERVER['DOCUMENT_ROOT'] . '/includes');

    // carregar as linguagens
    require_once $this->_lang . '.php';
    
    // objecto html
    require_once 'html.inc.php';
  }

  /**
   * Sets the title to this page.
   * @param String $title
   */
  public function setTitle($title) {
    $this->_title = $title;
  }

  /**
   * Gets current title.
   * @return String
   */
  public function getTitle() {
    return $this->_title;
  }
  
  public function setLang($lang) {
    $this->_lang = $lang;  
  }
  
  
  /**
   * Gets current lang.
   * @return String
   */
  public function getLang() {
    return $this->_lang;
  }

  /**
   * Sets the custom part of the head section on this page.
   * @param String $customHead The custom part of the head in the page.
   */
  public function setCustomHead($customHead) {
    $this->_customHead = $customHead;
  }

  /**
   * Gets current set custom head contents.
   * @return String
   */
  public function getCustomHead() {
    return $this->_customHead;
  }

  /**
   * Display the buffered page.
   */
  public function show() {
    $this->buildPage();
    echo $this->_page;
  }

  /**
   * Get's the current page contents.
   * @return String The current page.
   */
  public function getPage() {
    return $this->_page;
  }

  /**
   * Buffer the page, using current custom content.
   */
  private function buildPage() {
    ob_clean();
    ob_start();

    //session_start();
    require_once $this->_template;

    $this->_page = ob_get_clean();
  }

	/**
	*/
	public function setActiveMenu($val){
		$this->_active_menu = $val;
	}
	
	public function getActiveMenu(){
		return $this->_active_menu;
	}	
}
