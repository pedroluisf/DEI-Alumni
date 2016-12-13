<!DOCTYPE html>
<html lang="<?php echo $this->getLang(); ?>">
	<head>
		<title><?php echo $this->getTitle(); ?></title>
		<meta charset="utf-8">
		<link rel="stylesheet" href="css/reset.css" type="text/css" media="screen">
		<link rel="stylesheet" href="css/style.css" type="text/css" media="screen">
		<link rel="stylesheet" href="css/grid.css" type="text/css" media="screen">
		<script src="js/jquery-1.6.3.min.js" type="text/javascript"></script>
		<script src="js/cufon-yui.js" type="text/javascript"></script>
		<script src="js/cufon-replace.js" type="text/javascript"></script>
		<script src="js/Mate_400.font.js" type="text/javascript"></script>
		<script src="js/FF-cash.js" type="text/javascript"></script>
		<!--[if lt IE 7]>
		<div style=' clear: both; text-align:center; position: relative;'>
			<a href="http://windows.microsoft.com/en-US/internet-explorer/products/ie/home?ocid=ie6_countdown_bannercode">
				<img src="http://storage.ie6countdown.com/assets/100/images/banners/warning_bar_0000_us.jpg" border="0" height="42" width="820" alt="You are using an outdated browser. For a faster, safer browsing experience, upgrade for free today." />
			</a>
		</div>
		<![endif]-->
		<!--[if lt IE 9]>
			<script type="text/javascript" src="js/html5.js"></script>
			<link rel="stylesheet" href="css/ie.css" type="text/css" media="screen">
		<![endif]-->
	</head>
	<body id="page5">
		<div class="extra">
			<div class="main">
<!--==============================header=================================-->
				<header>
          <?php require_once 'menu.inc.php'; ?>
				</header>
<!--==============================content================================-->
				<section id="content">
					<div class="container_12">
						<div class="wrapper p4">
							<article class="grid_4">
								<div class="box">
									<div class="padding">
										<h3 class="p1"><?php echo DEI_CONTACTS; ?></h3>
										<dl>
											<dt><span><?php echo DEI_CLASS; ?>:</span>3NB</dt>
											<dd>
                        <span>Email:</span>
                        <a class="link" href="#">1090702@isep.ipp.pt</a>
                        <span>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
                        <a class="link" href="#">1090988@isep.ipp.pt</a>
                        <span>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
                        <a class="link" href="#">1090949@isep.ipp.pt</a>
                        <span>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
                        <a class="link" href="#">1091022@isep.ipp.pt</a>
                      </dd>
										</dl>
									</div>
								</div>
							</article>
							<article class="grid_8">
								<div class="box">
									<div class="padding">
										<h3 class="p1"><?php echo DEI_MEMBERS; ?></h3>
										1090702 - Pedro Ferreira <br/>
                    1090988 - Sérgio Sousa <br/>
                    1090949 - Manuel Monteiro <br/>
                    1091022 - Pedro Magueija <br/>
									</div>
								</div>
							</article>
						</div>
            <div class="wrapper">
							<article class="grid_12">
								<div class="indent-left2">
									<h3 class="p1">Contact Form</h3>
									<form id="contact-form" method="post" enctype="multipart/form-data">
										<fieldset>
											  <label><span class="text-form">Your Name:</span><input name="p1" type="text" /></label>
											  <label><span class="text-form">Your E-mail:</span><input name="p2" type="text" /></label>
											  <div class="wrapper">
												<div class="text-form">Your Message:</div>
												<div class="extra-wrap">
													<textarea></textarea>
													<div class="clear"></div>
													<div class="buttons">
														<a class="button" href="#" onClick="document.getElementById('contact-form').reset()"><?php echo DEI_CLEAR; ?></a>
														<a class="button" href="#" onClick="document.getElementById('contact-form').submit()"><?php echo DEI_SUBMIT; ?></a>
													</div>
												</div>
											  </div>
										</fieldset>
									</form>
								</div>
							</article>
						</div>
					</div>
					<div class="block"></div>
				</section>
			</div>
		</div>
<!--==============================footer=================================-->
		<?php html_footer(); ?>
		<script type="text/javascript"> Cufon.now(); </script>
	</body>
</html>