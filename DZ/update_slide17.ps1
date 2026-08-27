$ErrorActionPreference='Stop'
$file=Join-Path $PSScriptRoot 'Цветовосприятие — рабочая презентация.pptx'
$image=Join-Path $PSScriptRoot 'assets\eye.svg'
$msoFalse=0;$msoTrue=-1
function RGB([int]$r,[int]$g,[int]$b){$r+256*$g+65536*$b}
$navy=RGB 21 31 51;$cream=RGB 247 244 238;$coral=RGB 239 101 87;$ink=RGB 37 45 59;$white=RGB 255 255 255;$gray=RGB 108 117 131
function Text($s,$x,$y,$w,$h,$v,$size,$color,$bold=$false,$align=1){$o=$s.Shapes.AddTextbox(1,$x,$y,$w,$h);$o.TextFrame.TextRange.Text=$v;$o.TextFrame.TextRange.Font.Name='Aptos';$o.TextFrame.TextRange.Font.Size=$size;$o.TextFrame.TextRange.Font.Bold=$(if($bold){$msoTrue}else{$msoFalse});$o.TextFrame.TextRange.Font.Color.RGB=$color;$o.TextFrame.TextRange.ParagraphFormat.Alignment=$align;$o.TextFrame.MarginLeft=0;$o.TextFrame.MarginRight=0;$o.TextFrame.MarginTop=0;$o.TextFrame.MarginBottom=0;$o}
function Rect($s,$x,$y,$w,$h,$fill,$round=$false){$o=$s.Shapes.AddShape($(if($round){5}else{1}),$x,$y,$w,$h);$o.Fill.ForeColor.RGB=$fill;$o.Line.Visible=$msoFalse;$o}
function AddFittedPicture($s,$path,$x,$y,$w,$h){$p=$s.Shapes.AddPicture($path,$msoFalse,$msoTrue,$x,$y,-1,-1);$p.LockAspectRatio=$msoTrue;if(($p.Width/$p.Height)-gt($w/$h)){$p.Width=[single]$w;$p.Left=[single]$x;$p.Top=[single]($y+($h-$p.Height)/2)}else{$p.Height=[single]$h;$p.Top=[single]$y;$p.Left=[single]($x+($w-$p.Width)/2)};$p}
$ppt=New-Object -ComObject PowerPoint.Application;$ppt.Visible=$msoTrue;$pres=$ppt.Presentations.Open($file,0,0,0)
try{
  $s=$pres.Slides.Item(17);for($i=$s.Shapes.Count;$i -ge 1;$i--){$s.Shapes.Item($i).Delete()}
  $s.FollowMasterBackground=$msoFalse;$s.Background.Fill.ForeColor.RGB=$cream
  Rect $s 0 0 960 10 $coral|Out-Null
  Text $s 52 28 820 46 'Выводы' 28 $navy $true|Out-Null
  Text $s 890 35 30 22 '17' 11 $gray $true 2|Out-Null
  Rect $s 48 92 500 414 $white $true|Out-Null
  $text="Цвет не является неизменным свойством объекта, а возникает в результате взаимодействия спектра света, поверхности, зрительной системы и условий наблюдения. Три типа колбочек кодируют свет перекрывающимися спектральными ответами, после чего нервная система обрабатывает сигналы в оппонентных каналах. Поэтому разные спектральные распределения могут восприниматься одинаково, а одинаковый физический стимул — выглядеть по-разному в зависимости от окружения и адаптации.`n`nКомпьютерная графика использует эту особенность, формируя широкий набор ощущений цвета с помощью трёх первичных компонентов дисплея. Однако RGB-значения приобретают однозначный смысл только внутри заданного цветового пространства. sRGB, Display P3 и Adobe RGB отличаются первичными цветами и охватом, а CIE XYZ и Lab позволяют связывать цвет с измерениями и воспринимаемыми различиями. Ни камера, ни монитор, ни принтер не способны воспроизвести весь диапазон видимых цветов. ICC-профили, преобразование охвата и калибровка делают результат более предсказуемым, но не устраняют физических ограничений устройств.`n`nОсобенности зрения необходимо учитывать при рендеринге, tone mapping, интерполяции градиентов, цветокоррекции и визуализации данных. Вычисления освещения и смешения следует выполнять в линейном пространстве, а для зрительно равномерных изменений подходят перцептивные модели. Доступная графика дополнительно требует достаточного контраста и передачи смысла не только оттенком, но также формой, подписью или узором. Таким образом, корректная работа с цветом объединяет физику света, физиологию зрения, математику цветовых пространств и характеристики устройств. Понимание человеческого цветовосприятия позволяет создавать изображения, которые выглядят правдоподобно, сохраняют нужные различия и остаются понятными для разных пользователей."
  Text $s 68 112 460 374 $text 10 $ink|Out-Null
  AddFittedPicture $s $image 585 132 310 310|Out-Null
  $pres.Save()
}finally{$pres.Close();$ppt.Quit();[Runtime.InteropServices.Marshal]::ReleaseComObject($pres)|Out-Null;[Runtime.InteropServices.Marshal]::ReleaseComObject($ppt)|Out-Null;[GC]::Collect();[GC]::WaitForPendingFinalizers()}
