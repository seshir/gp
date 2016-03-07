<?php
/**
 * @file
 * Default theme implementation to format an HTML mail.
 *
 * Copy this file in your default theme folder to create a custom themed mail.
 * Rename it to mimemail-message--[module]--[key].tpl.php to override it for a
 * specific mail.
 *
 * Available variables:
 * - $recipient: The recipient of the message
 * - $subject: The message subject
 * - $body: The message body
 * - $css: Internal style sheets
 * - $module: The sending module
 * - $key: The message identifier
 *
 * @see template_preprocess_mimemail_message()
 */
?>
<?php
global $base_url;
$logo_path = theme_get_setting('logo', 'elvyre');
$logo = "<img src='" . $logo_path . "' />";
$site_name = variable_get('site_name');
?>
<html>
  <head>
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
  </head>
  <body id="mimemail-body" <?php if ($module && $key): print 'class="' . $module . '-' . $key . '"';
endif; ?>>
    <div id="center" style="font-family: Arial, sans-serif;">
      <div id="main">
        <table style="border-collapse: collapse; border-spacing: 0;">
          <thead><tr class="email-header" style="background-color: #D7D4D3;">
              <td class="email-logo" style="width: 268px; padding: 10px 0 10px 20px;">
                <?php print $logo; ?>
              </td>
              <td class="email-sitename" style="vertical-align: middle;">
                <h3 style="margin: 0;"><?php print $site_name; ?></h3>
              </td>
            </tr></thead>
          <tbody style="background-color: #F5F5F5;"><tr>
              <td colspan="2" class="email-body" style="padding: 20px; text-align: justify;">
                <p><?php print $body; ?></p>
              </td>
            </tr>
          </tbody>
        </table>
      </div>
    </div>
  </body>
</html>
