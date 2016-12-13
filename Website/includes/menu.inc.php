<div class="wrapper p4">
  <h1><a href="index.php">DEI ALUMNI</a></h1>
  <ul class="list-services">
  	<li><a href="<?php echo $_SERVER['PHP_SELF'] . "?lang=pt"; ?>">PT</a> | <a href="<?php echo $_SERVER['PHP_SELF'] . "?lang=en"; ?>">UK</a></li>
    <?php
	if (isset($_SESSION["DEI_user"])) {
		echo "<li>" . DEI_WELCOME . " " . $_SESSION["DEI_user"] . ", ";
		echo "<a href=\"logout.php\">" . DEI_LOGOUT . "</a></li>";
	} else {
		echo "<li><a href=\"login.php\">" . DEI_LOGIN . "</a></li>";
		echo "<li><a href=\"register.php\">" . DEI_REGISTER . "</a></li>";
	}
	?>
  </ul>
</div>
<nav>
  <ul class="menu">
    <li <?php if ($this->getActiveMenu() == 1) echo "class=\"active\""; ?>><a href="index.php">Home</a></li>
    <li <?php if ($this->getActiveMenu() == 2) echo "class=\"active\""; ?>><a href="ranking.php"><?php echo DEI_RANKING; ?></a></li>
    <li <?php if ($this->getActiveMenu() == 3) echo "class=\"active\""; ?>><a href="work.php"><?php echo DEI_TOURNAMENT; ?></a></li>
    <li <?php if ($this->getActiveMenu() == 4) echo "class=\"active\""; ?>><a href="downloads.php"><?php echo DEI_DOWNLOADS; ?></a></li>
    <li class="last <?php if ($this->getActiveMenu() == 5) echo "active"; ?>"><a href="contacts.php"><?php echo DEI_CONTACTS; ?></a></li>
  </ul>
</nav>
