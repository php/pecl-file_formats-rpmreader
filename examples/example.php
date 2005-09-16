<?
/* $Id$ */

$rpmf = rpm_open("/path/to/rpm/file/file.rpm");

if($rpmf)
{
  echo "RPM file opened...<br>\n";
  $data = rpm_get_tag($rpmf, RPMREADER_NAME);
  if ($data == false)
    {
      echo "not found<br>\n";
    }
  else
    {
      $data = htmlspecialchars($data);
      echo "Value: $data<br>\n";
    }
  rpm_close($rpmf);
}
else
{
  echo "Could not open RPM file!<br>\n";
}

?>
