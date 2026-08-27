$ErrorActionPreference='Stop'
$file=Join-Path $PSScriptRoot 'Цветовосприятие — рабочая презентация.pptx'
$image=Join-Path $PSScriptRoot 'assets\icc_workflow_english.jpg'
$msoFalse=0;$msoTrue=-1;$msoPicture=13
$ppt=New-Object -ComObject PowerPoint.Application;$ppt.Visible=$msoTrue;$pres=$ppt.Presentations.Open($file,0,0,0)
try{
  $s=$pres.Slides.Item(13)
  for($i=$s.Shapes.Count;$i -ge 1;$i--){$sh=$s.Shapes.Item($i);if($sh.Type -eq $msoPicture){$sh.Delete()}}
  $p=$s.Shapes.AddPicture($image,$msoFalse,$msoTrue,535,132,385,310);$p.LockAspectRatio=$msoTrue;$p.Width=[single]385;$p.Left=[single]535;$p.Top=[single](132+(310-$p.Height)/2)
  $pres.Save()
}finally{$pres.Close();$ppt.Quit();[Runtime.InteropServices.Marshal]::ReleaseComObject($pres)|Out-Null;[Runtime.InteropServices.Marshal]::ReleaseComObject($ppt)|Out-Null;[GC]::Collect();[GC]::WaitForPendingFinalizers()}
