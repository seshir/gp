
        <!-- .header-wrapper start -->
        <div id="header-wrapper" class="clearfix">
            <!-- .top-bar start -->
            <section id="top-bar-wrapper">
                <div id="top-bar" class="clearfix">
                 <!-- .container start -->
                <div class="container">
                 <!-- .row start -->
                 <div class="row">
                 <section id="nav-container">
                     <nav id="nav">
                         <?php print render($page['main_menu']); ?>
                     </nav><!-- #nav end -->
                 </section><!-- #nav-container end -->
                 </div><!-- .container end -->
                 </div><!-- .row end -->
                </div><!-- .top-bar end -->
            </section><!-- .top-bar-wrapper end -->

            <!-- #header start -->
            <header id="header" class="clearfix">
               <!--  // <?php $block = module_invoke('search', 'block_view', 'search'); print render($block); ?> //  -->
            </header><!-- .header end -->
            <div class="home-logo">
                <div class="home-logo-1">
                    <?php if ($logo): ?>
                        <section id="logo">
                            <a href="<?php print $front_page; ?>"><img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" /></a>
                        </section>
                    <?php endif; ?>

                    <?php if ($site_slogan): ?>
                        <div id="tagline" class="font_heading">
                            <?php print $site_slogan; ?>
                        </div>
                    <?php endif; ?>
                    <span class="banner-text">
                        <p>
                            <b>You’ll never lose receipt again!</b><br/> With our My Pop your proof of purchase is stored safely and securely on one easy to use app.
                        </p>
                    </span>
                    <div class="download-app">
                        <a href="#"><img src="<?php print drupal_get_path('theme','elvyre')?>/img/mypop/AppStore.png" class="download-app-icon app-store" /></a>
                        <a href="https://play.google.com/store/apps/details?id=com.mypop.app.beta&hl=en"><img src="<?php print drupal_get_path('theme','elvyre')?>/img/mypop/PlayStore.png" class="download-app-icon play-store" /></a>
                    </div>
                </div>
                <div class="download-arrow">
                    <a href="#arrow-down-app">&nbsp;</a>
                </div>
                <div class="container" id="header-stmt">
                        <span>
                            <p>
                                <span><b>You use your phone for everything else, why not your receipts?</b></span>
                                <span>Now keep track of your purchases has never been easier.</span>
                            </p>
                        </span>
                    </div>
                </div>

        </div><!-- .header-wrapper end -->
         <?php if ($page['page_title']): ?>
         <?php if (!drupal_is_front_page()): ?>
                <!-- #page-title start -->
        <section id="page-title" class="page-title-1" data-stellar-background-ratio="0.5">
            <div class="container">
                <div class="row">
                    <div class="grid_8">
                     <?php print render($page['page_title']); ?>
                        
                    </div><!-- .grid_8 end -->

                    <!-- .grid_4 start -->
                    <div class="grid_4">
                        <div class="pt-image-container">
                        <?php print render($page['pt_image']); ?>
                            
                        </div>
                    </div><!-- .grid_4 end -->
                </div><!-- .row end -->

                <div class="row">
                    <div class="grid_8">
                        <div class="breadcrumbs bc2 triggerAnimation animated" data-animate="fadeInUp">
                            <?php print $breadcrumb; ?>
                        </div>
                    </div>
                </div>
            </div><!-- .container end -->
        </section><!-- #page-title end -->
         <?php endif; ?>
        <?php endif; ?>
        
        <?php if (!$page['page_title'] || !$page['pt_image'] ) : ?>
        
         <?php if($breadcrumb && !$is_front): ?>
             <section id="page-title" class="page-title-3">
               <div class="container">
                <div class="row">
                  <div class="grid_12">
                    <div class="breadcrumbs bc triggerAnimation animated" data-animate="fadeInUp">
                  <?php print $breadcrumb; ?>
                    </div>
                  </div><!-- .grid_12 end -->
                 </div><!-- .row end -->
               </div><!-- .container end -->
            </section>
	  <?php endif; ?>
      <?php endif; ?>
       
        

        <!-- .tp-wrapper start -->
        <div class="tp-wrapper">
            <!-- .tp-banner-container start -->
            <div class="tp-banner-container">
                <div class="tp-banner">
                    <?php if ($page['slider']): ?><?php print render($page['slider']); ?><?php endif; ?>
                </div><!-- .tp-banner end -->
            </div><!-- .tp-banner end -->
        </div><!-- .tp-wrapper end -->

        
                        
                        <?php if ($page['featured']): ?>
                        <!-- .page-content start -->
        <section class="page-content background-black">
            <!-- .container start -->
            <div class="container">
                <!-- .row start -->
                <div class="row">
                    <article class="grid_12">
                        <div class="triggerAnimation animated" data-animate="fadeInUp">
                         <div class="note no-bottom-margin">
                        <?php print render($page['featured']); ?>
                         </div>
                        </div><!-- .triggerAnimation.animated end -->
                    </article><!-- .grid_12 end -->
                </div><!-- .row end -->
            </div><!-- .container end -->
        </section><!-- .page-content end -->
                        <?php endif; ?> 
                        



                    <?php if ($page['content_parallax_1']): ?>
        <!-- .page-content start -->
        <section class="page-content parallax parallax-1" data-stellar-background-ratio="0.5">
            <!-- .container start -->
            <div class="container">
                <!-- .row start -->
                <div class="row">
                    <article class="grid_12">
                     <?php print render($page['content_parallax_1']); ?>
                        
                    </article><!-- .grid_12 end -->                    
                </div><!-- .row end -->
            </div><!-- .container end -->
        </section><!-- .page-content end -->
                   <?php endif; ?> 
        <section class='page-content' id="main-container">
            <div class="container">
                <div class="row">

          <?php if ( ($page['sidebar_left']) ) : ?>
		  <aside class="grid_3 aside-left triggerAnimation animated" data-animate="fadeInLeft">
		  <?php print render($page['sidebar_left']); ?>
		  </aside>
		  <?php endif; ?>

          <?php if ( ($page['sidebar_right']) AND (!$page['sidebar_left']) ): ?>
		  <article class="grid_9 triggerAnimation animated" data-animate="fadeInLeft">
		  <?php endif; ?>
          <?php if ( (!$page['sidebar_right']) AND ($page['sidebar_left']) ): ?>
		  <article class="grid_9 triggerAnimation animated" data-animate="fadeInRight">
		  <?php endif; ?>
		  
		  <?php if ( ($page['sidebar_right']) AND ($page['sidebar_left']) ): ?>
		   <article class="grid_6 triggerAnimation animated" data-animate="fadeInLeft">
		  <?php endif; ?>
          <?php if ( (!$page['sidebar_right']) AND (!$page['sidebar_left']) ): ?>
		   <article class="article grid_12">
		  <?php endif; ?>

          <?php if ($messages): ?>
                
                <div id="messages">
                <?php print $messages; ?>
                </div>
             
                <?php endif; ?>
         <?php if ($title): ?><h1 class="title" id="pt"><?php print $title; ?></h1><?php endif; ?>
                
        <?php if ($tabs): ?><div class="d-tabs"><?php print render($tabs); ?></div><?php endif; ?>
        <?php print render($page['help']); ?>
        <?php if ($action_links): ?><ul class="action-links"><?php print render($action_links); ?></ul><?php endif; ?>
        <?php print render($page['content']); ?>
                  </article><!-- .article end -->
                            
          <?php if ( ($page['sidebar_right']) ) : ?>
		  <aside class="grid_3 aside-right triggerAnimation animated" data-animate="fadeInRight">
		  <?php print render($page['sidebar_right']); ?>
		  </aside>
		  <?php endif; ?>
                 
                </div><!-- .row end -->
            </div><!-- .container end -->
        </section><!-- .page-content end -->
        
           <?php if ($page['content_parallax_2']): ?>

        <!-- .page-content.parallax start -->
        <section class="page-content parallax parallax-2">
            <!-- .container start -->
            <div class="container">
            
             <?php print render($page['content_parallax_2']); ?>
             
              <?php endif; ?> 
               
            </div><!-- .container end -->
        </section><!-- .page-content.parallax.parallax-2 end -->

        <section class="page-content">
            <div class="container">
            <?php if ($page['postscript_first']): ?>
                <!-- .row start -->
                <div class="row">
                    <article class="grid_12">
                        <section class="heading-centered triggerAnimation animated" data-animate="bounceIn">
                            <?php print render($page['postscript_first']); ?>
                        </section>
                    </article><!-- .grid_12 end -->

                </div><!-- .row end -->
             <?php endif; ?>
              
            </div><!-- .container end -->
        </section><!-- .page-content end -->
        
        <?php if ($page['content_parallax_3']): ?>
        <!-- .page-content.parallax start -->
       <section class="page-content parallax parallax-3" data-stellar-background-ratio="0.5">
            <!-- .container start -->
            <div class="container">
            
            
             <?php print render($page['content_parallax_3']); ?>
             
              <?php endif; ?> 
                
            </div><!-- .container end -->
        </section><!-- .page-content.parallax end -->
        
                <section class="page-content">
            <div class="container">
            <?php if ($page['postscript_second']): ?>
                <!-- .row start -->
                <div class="row">
                    <article class="grid_12">
                        <section class="heading-centered triggerAnimation animated" data-animate="bounceIn">
                            <?php print render($page['postscript_second']); ?>
                        </section>
                    </article><!-- .grid_12 end -->

                </div><!-- .row end -->
             <?php endif; ?>
              
            </div><!-- .container end -->
        </section><!-- .page-content end -->


         <?php if ($page['content_parallax_4']): ?>
        <!-- .page-content.parallax start -->
        <section class="page-content parallax parallax-4">
            <!-- .container start -->
            <div class="container">
            
            
             <?php print render($page['content_parallax_4']); ?>
             
              <?php endif; ?> 
                
            </div><!-- .container end -->
        </section><!-- .page-content.parallax end -->
        
        <?php if($page['postscript_third'] || $page['postscript_fourth']) : ?>
        <section class="page-content">
            <div class="container">
            <div class="row">
            <?php if ($page['postscript_third']): ?>
            
                    <article class="grid_9">
                        <div class="triggerAnimation animated" data-animate='fadeInLeft'>
                     <?php print render($page['postscript_third']); ?>
                       </div><!-- .triggerAnimation.animated end -->
                    </article>
                   <?php endif; ?> 
              <?php if ($page['postscript_fourth']): ?>     
                    <article class="grid_3">
                        <div class="triggerAnimation animated" data-animate="fadeInRight">
                        <?php print render($page['postscript_fourth']); ?>
                       
                        </div>
                         </article>
                        <?php endif; ?> 
           </div><!-- .row end -->          
         </div><!-- .container end -->
        </section><!-- .page-content.parallax end -->
<?php endif; ?>
       
                <?php if ($page['bottom']): ?>
                 <section class="page-content">
                 <div class="container">
                 <div class="row">
                 <?php print render($page['bottom']); ?>
                 </div><!-- .row end -->
                 </div><!-- .container end -->
                 </section><!-- .page-content end -->
                 <?php endif; ?> 
                    

        <!-- .footer-wrapper start -->
        <section class="footer-wrapper">
            <!-- .footer start -->
            <footer id="footer">
                <!-- .container start -->
                <div class="container">
                    <!-- .row start -->
                    <div class="row">

                        <!-- animated fadeInTop -->
                        <section class="triggerAnimation animated" data-animate="fadeIn">
                         <?php if ($page['footer_firstcolumn']): ?>
                         <!-- .footer-widget-container start -->
                         <div class="grid_3 footer-widget-container">                             
                         <!-- .widget.widget_text start -->
                         <div class="widget widget_text clearfix">
                         <?php print render($page['footer_firstcolumn']); ?>
                         </div>
                         </div>
                         <?php endif; ?>


                         <?php if ($page['footer_secondcolumn']): ?>
                         <!-- .footer-widget-container start -->
                         <div class="grid_3 footer-widget-container"> 
                         <?php print render($page['footer_secondcolumn']); ?>
                         </div>
                         <?php endif; ?>

                         <?php if ($page['footer_thirdcolumn']): ?>
                         <div class="grid_3 footer-widget-container"> 
                         <?php print render($page['footer_thirdcolumn']); ?>
                         </div>
                         <?php endif; ?>

                         <?php if ($page['footer_fourthcolumn']): ?>
                         <div class="grid_3 footer-widget-container"> 
                         <?php print render($page['footer_fourthcolumn']); ?>
                         </div>
                         <?php endif; ?>
                           
                        </section>
                    </div><!-- .row end -->
                </div><!-- .container end -->                
            </footer><!-- .footer-end -->

            <!-- .copyright-container start -->
            <div class="copyright-container">
                <!-- .container start -->
                <div class="container">
                    <!-- .row start -->
                    <div class="row">
                        <section class="grid_6">
                         <?php if ($page['footer-a']): ?>
                         <?php print render($page['footer-a']); ?>
                         <?php endif; ?>  
                        </section>

                        <section class="grid_6">
                        <?php if ($page['footer-b']): ?>
                        <?php print render($page['footer-b']); ?>
                        <?php endif; ?>
                        </section>
                    </div><!-- .row end -->
                </div><!-- .container end -->
            </div><!-- .copyright-container end -->

            <a href="#" class="scroll-up">Scroll</a>
        </section><!-- .footer-wrapper end -->
