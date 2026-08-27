$ErrorActionPreference='Stop'
$file=Join-Path $PSScriptRoot 'Цветовосприятие — рабочая презентация.pptx'
$image=Join-Path $PSScriptRoot 'assets\wcag_contrast_example.png'
$msoFalse=0;$msoTrue=-1
function RGB([int]$r,[int]$g,[int]$b){$r+256*$g+65536*$b}
$navy=RGB 21 31 51;$cream=RGB 247 244 238;$coral=RGB 239 101 87;$ink=RGB 37 45 59;$white=RGB 255 255 255;$gray=RGB 108 117 131
function Text($s,$x,$y,$w,$h,$v,$size,$color,$bold=$false,$align=1){$o=$s.Shapes.AddTextbox(1,$x,$y,$w,$h);$o.TextFrame.TextRange.Text=$v;$o.TextFrame.TextRange.Font.Name='Aptos';$o.TextFrame.TextRange.Font.Size=$size;$o.TextFrame.TextRange.Font.Bold=$(if($bold){$msoTrue}else{$msoFalse});$o.TextFrame.TextRange.Font.Color.RGB=$color;$o.TextFrame.TextRange.ParagraphFormat.Alignment=$align;$o.TextFrame.MarginLeft=0;$o.TextFrame.MarginRight=0;$o.TextFrame.MarginTop=0;$o.TextFrame.MarginBottom=0;$o}
function Rect($s,$x,$y,$w,$h,$fill,$round=$false){$o=$s.Shapes.AddShape($(if($round){5}else{1}),$x,$y,$w,$h);$o.Fill.ForeColor.RGB=$fill;$o.Line.Visible=$msoFalse;$o}
function AddFittedPicture($s,$path,$x,$y,$w,$h){$p=$s.Shapes.AddPicture($path,$msoFalse,$msoTrue,$x,$y,-1,-1);$p.LockAspectRatio=$msoTrue;if(($p.Width/$p.Height)-gt($w/$h)){$p.Width=[single]$w;$p.Left=[single]$x;$p.Top=[single]($y+($h-$p.Height)/2)}else{$p.Height=[single]$h;$p.Top=[single]$y;$p.Left=[single]($x+($w-$p.Width)/2)};$p}
$ppt=New-Object -ComObject PowerPoint.Application;$ppt.Visible=$msoTrue;$pres=$ppt.Presentations.Open($file,0,0,0)
try{
  $s=$pres.Slides.Item(16);for($i=$s.Shapes.Count;$i -ge 1;$i--){$s.Shapes.Item($i).Delete()}
  $s.FollowMasterBackground=$msoFalse;$s.Background.Fill.ForeColor.RGB=$cream
  Rect $s 0 0 960 10 $coral|Out-Null
  Text $s 52 28 820 46 'Как сделать цвет в интерфейсе доступным?' 28 $navy $true|Out-Null
  Text $s 890 35 30 22 '16' 11 $gray $true 2|Out-Null
  Rect $s 48 92 470 414 $white $true|Out-Null
  $text="Доступный интерфейс должен оставаться понятным людям с пониженной контрастной чувствительностью и различными типами цветового зрения. Рекомендации WCAG 2.2 требуют для обычного текста коэффициент контраста не ниже 4,5:1. Для крупного текста допускается отношение 3:1, поскольку широкий штрих распознаётся легче. Коэффициент вычисляется по относительной яркости переднего плана и фона, а не просто по различию цветовых тонов.`n`nВысокая насыщенность сама по себе не гарантирует читаемость: два ярких цвета могут иметь почти одинаковую светлоту. Текст поверх фотографии необходимо проверять в самых светлых и тёмных участках либо отделять однотонной подложкой. Стандарт также запрещает использовать цвет как единственный способ передачи информации. Например, ошибочное поле следует обозначать не только красной рамкой, но и значком или текстовым сообщением. Ссылки внутри абзаца можно дополнительно подчёркивать, а активные состояния — различать формой, контуром или подписью.`n`nВ диаграммах категории полезно кодировать одновременно цветом, штриховкой, маркером или непосредственной подписью. Особенно ненадёжны пары красный–зелёный и синий–фиолетовый, потому что они могут сливаться при распространённых нарушениях цветового зрения. Однако универсального набора «безопасных» оттенков не существует: различимость зависит также от яркости, размера элементов и фона. Поэтому макет проверяют инструментом измерения контраста и симуляцией протанопии, дейтеранопии и тританопии. Симуляция не заменяет тестирование с пользователями, но помогает заранее обнаружить зависимость интерфейса от цветовых различий. Учёт особенностей цветовосприятия делает графику понятнее не только людям с нарушениями зрения, но и пользователям тусклых экранов, проекторов и устройств при ярком внешнем освещении."
  Text $s 68 112 430 374 $text 10 $ink|Out-Null
  AddFittedPicture $s $image 535 132 390 310|Out-Null
  $pres.Save()
}finally{$pres.Close();$ppt.Quit();[Runtime.InteropServices.Marshal]::ReleaseComObject($pres)|Out-Null;[Runtime.InteropServices.Marshal]::ReleaseComObject($ppt)|Out-Null;[GC]::Collect();[GC]::WaitForPendingFinalizers()}
