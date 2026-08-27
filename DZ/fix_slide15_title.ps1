$ErrorActionPreference='Stop'
$file=Join-Path $PSScriptRoot 'Цветовосприятие — рабочая презентация.pptx'
$msoTrue=-1
$ppt=New-Object -ComObject PowerPoint.Application;$ppt.Visible=$msoTrue;$pres=$ppt.Presentations.Open($file,0,0,0)
try{
  $s=$pres.Slides.Item(15)
  for($i=1;$i -le $s.Shapes.Count;$i++){
    $sh=$s.Shapes.Item($i)
    if($sh.HasTextFrame -eq $msoTrue){
      $value=$sh.TextFrame.TextRange.Text
      if($value -eq 'Цветовосприятие в обработке изображений'){$sh.TextFrame.TextRange.Text='Цвет и обработка изображений'}
      elseif($value -eq 'Цвет и обработка изображений' -and $sh.Width -gt 900){$sh.TextFrame.TextRange.Text=''}
    }
  }
  $pres.Save()
}finally{$pres.Close();$ppt.Quit();[Runtime.InteropServices.Marshal]::ReleaseComObject($pres)|Out-Null;[Runtime.InteropServices.Marshal]::ReleaseComObject($ppt)|Out-Null;[GC]::Collect();[GC]::WaitForPendingFinalizers()}
