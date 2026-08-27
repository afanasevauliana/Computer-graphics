$ErrorActionPreference='Stop'
$file=Join-Path $PSScriptRoot 'Цветовосприятие — рабочая презентация.pptx'
$image=Join-Path $PSScriptRoot 'assets\rgb_hsv_hsl.png'
$msoFalse=0;$msoTrue=-1
function RGB([int]$r,[int]$g,[int]$b){$r+256*$g+65536*$b}
$navy=RGB 21 31 51;$cream=RGB 247 244 238;$coral=RGB 239 101 87;$ink=RGB 37 45 59;$white=RGB 255 255 255;$gray=RGB 108 117 131
function Text($s,$x,$y,$w,$h,$v,$size,$color,$bold=$false,$align=1){$o=$s.Shapes.AddTextbox(1,$x,$y,$w,$h);$o.TextFrame.TextRange.Text=$v;$o.TextFrame.TextRange.Font.Name='Aptos';$o.TextFrame.TextRange.Font.Size=$size;$o.TextFrame.TextRange.Font.Bold=$(if($bold){$msoTrue}else{$msoFalse});$o.TextFrame.TextRange.Font.Color.RGB=$color;$o.TextFrame.TextRange.ParagraphFormat.Alignment=$align;$o.TextFrame.MarginLeft=0;$o.TextFrame.MarginRight=0;$o.TextFrame.MarginTop=0;$o.TextFrame.MarginBottom=0;$o}
function Rect($s,$x,$y,$w,$h,$fill,$round=$false){$o=$s.Shapes.AddShape($(if($round){5}else{1}),$x,$y,$w,$h);$o.Fill.ForeColor.RGB=$fill;$o.Line.Visible=$msoFalse;$o}
$ppt=New-Object -ComObject PowerPoint.Application;$ppt.Visible=$msoTrue;$pres=$ppt.Presentations.Open($file,0,0,0)
try{
  $s=$pres.Slides.Item(11);for($i=$s.Shapes.Count;$i -ge 1;$i--){$s.Shapes.Item($i).Delete()}
  $s.FollowMasterBackground=$msoFalse;$s.Background.Fill.ForeColor.RGB=$cream
  Rect $s 0 0 960 10 $coral|Out-Null;Text $s 52 28 820 46 'Как связаны зрение и цветовые модели?' 28 $navy $true|Out-Null;Text $s 890 35 30 22 '11' 11 $gray $true 2|Out-Null
  Rect $s 48 92 445 414 $white $true|Out-Null
  $text="Цветовая модель — это математический способ представления цвета набором координат. Её нельзя полностью отождествлять с механизмом человеческого зрения. Физиологическая система LMS описывает относительные ответы коротко-, средне- и длинноволновых колбочек. Модель RGB задаёт цвет интенсивностями трёх первичных компонентов устройства или рабочего пространства.`n`nКоординаты RGB удобны для хранения изображений и вычислений, но не являются перцептивно равномерными. Одинаковое числовое изменение RGB в разных областях пространства может создавать различную по заметности цветовую разницу. Модели HSV и HSL получаются геометрическим преобразованием RGB и предназначены прежде всего для удобного выбора и редактирования цвета. В них цветовой тон задаётся углом, насыщенность — расстоянием от нейтральной оси, а Value или Lightness — вертикальной координатой. Эти параметры интуитивнее RGB, но также не соответствуют зрительному восприятию равномерно. Например, чистые синий и жёлтый с одинаковой Lightness в HSL выглядят неодинаково светлыми.`n`nСистема CIE XYZ основана на экспериментах по сопоставлению цветов со стандартным наблюдателем и служит независимым от устройства колориметрическим представлением. Пространство CIELAB является нелинейным преобразованием XYZ и было разработано для более равномерного описания воспринимаемых различий. Координата L* характеризует светлоту, a* — направление от зелёного к красному, а b* — от синего к жёлтому. Расстояние между точками в CIELAB используется в формулах цветового различия ΔE. Поэтому выбор модели зависит от задачи: RGB подходит для рендеринга и дисплеев, HSV/HSL — для интерфейсов выбора цвета, а XYZ и Lab — для измерения и управления цветом."
  Text $s 68 112 405 374 $text 10 $ink|Out-Null
  $pic=$s.Shapes.AddPicture($image,$msoFalse,$msoTrue,515,132,410,310);$pic.LockAspectRatio=$msoTrue;$pic.Width=410
  $pres.Save()
}finally{$pres.Close();$ppt.Quit();[Runtime.InteropServices.Marshal]::ReleaseComObject($pres)|Out-Null;[Runtime.InteropServices.Marshal]::ReleaseComObject($ppt)|Out-Null;[GC]::Collect();[GC]::WaitForPendingFinalizers()}
