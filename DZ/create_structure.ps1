$ErrorActionPreference = 'Stop'
$outPath = Join-Path $PSScriptRoot 'Цветовосприятие — рабочая презентация.pptx'
$blank = 12; $format = 24; $msoFalse = 0; $msoTrue = -1
function RGB([int]$r,[int]$g,[int]$b){$r+256*$g+65536*$b}
$navy=RGB 21 31 51; $cream=RGB 247 244 238; $coral=RGB 239 101 87
$cyan=RGB 46 196 182; $white=RGB 255 255 255; $gray=RGB 108 117 131; $light=RGB 232 237 244
function Text($slide,$x,$y,$w,$h,$value,$size,$color,$bold=$false,$align=1){
  $s=$slide.Shapes.AddTextbox(1,$x,$y,$w,$h);$s.TextFrame.TextRange.Text=$value
  $s.TextFrame.TextRange.Font.Name='Aptos';$s.TextFrame.TextRange.Font.Size=$size
  $s.TextFrame.TextRange.Font.Bold=$(if($bold){$msoTrue}else{$msoFalse});$s.TextFrame.TextRange.Font.Color.RGB=$color
  $s.TextFrame.TextRange.ParagraphFormat.Alignment=$align
  $s.TextFrame.MarginLeft=0;$s.TextFrame.MarginRight=0;$s.TextFrame.MarginTop=0;$s.TextFrame.MarginBottom=0;$s
}
function Rect($slide,$x,$y,$w,$h,$fill,$round=$false){
  $s=$slide.Shapes.AddShape($(if($round){5}else{1}),$x,$y,$w,$h);$s.Fill.ForeColor.RGB=$fill;$s.Line.Visible=$msoFalse;$s
}
$titles=@(
  'Особенности человеческого цветовосприятия',
  'Что такое цвет',
  'Как человек воспринимает цвет',
  'Палочки и колбочки',
  'Основные теории цветовосприятия',
  'Особенности и эффекты цветовосприятия',
  'Цветовая константность и иллюзии',
  'Нарушения цветового зрения',
  'Как экран создаёт цвет',
  'Человеческое зрение и цветовые модели',
  'Цветовые пространства и ограничения устройств',
  'Применение цветовосприятия в компьютерной графике',
  'Доступность интерфейсов и изображений',
  'Выводы',
  'Источники'
)
$ppt=New-Object -ComObject PowerPoint.Application;$ppt.Visible=$msoTrue;$pres=$ppt.Presentations.Add()
$pres.PageSetup.SlideWidth=960;$pres.PageSetup.SlideHeight=540
try{
  $s=$pres.Slides.Add(1,$blank);$s.FollowMasterBackground=$msoFalse;$s.Background.Fill.ForeColor.RGB=$navy
  Rect $s 0 0 960 12 $coral|Out-Null
  Rect $s 690 70 180 180 $coral $true|Out-Null;Rect $s 760 190 130 130 (RGB 57 117 224) $true|Out-Null
  Rect $s 630 280 155 155 (RGB 248 196 74) $true|Out-Null
  Text $s 58 82 560 35 'ДОМАШНЯЯ РАБОТА ПО КОМПЬЮТЕРНОЙ ГРАФИКЕ' 15 $cyan $true|Out-Null
  Text $s 58 140 575 135 "Особенности человеческого`nцветовосприятия" 39 $white $true|Out-Null
  Rect $s 58 306 470 4 $coral|Out-Null
  Text $s 58 340 560 35 'Выполнила: Афанасьева Ю. Р.' 20 $light $true|Out-Null
  Text $s 58 382 560 30 'Группа ИУК4-43Б' 18 $light|Out-Null

  for($i=2;$i -le $titles.Count;$i++){
    $s=$pres.Slides.Add($i,$blank);$s.FollowMasterBackground=$msoFalse;$s.Background.Fill.ForeColor.RGB=$cream
    Rect $s 0 0 960 10 $coral|Out-Null
    Text $s 52 30 820 55 $titles[$i-1] 28 $navy $true|Out-Null
    Text $s 890 35 30 22 ('{0:00}' -f $i) 11 $gray $true 2|Out-Null
    Rect $s 52 118 856 322 $white $true|Out-Null
    Text $s 82 235 796 38 'Содержимое слайда будет добавлено после согласования' 18 $gray $false 2|Out-Null
    Text $s 52 495 856 18 'Рабочая структура презентации' 10 $gray|Out-Null
  }
  $pres.SaveAs($outPath,$format)
}finally{
  $pres.Close();$ppt.Quit();[Runtime.InteropServices.Marshal]::ReleaseComObject($pres)|Out-Null;[Runtime.InteropServices.Marshal]::ReleaseComObject($ppt)|Out-Null
  [GC]::Collect();[GC]::WaitForPendingFinalizers()
}
Write-Output $outPath
