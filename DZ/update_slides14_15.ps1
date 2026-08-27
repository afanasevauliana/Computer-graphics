$ErrorActionPreference='Stop'
$file=Join-Path $PSScriptRoot 'Цветовосприятие — рабочая презентация.pptx'
$tone=Join-Path $PSScriptRoot 'assets\tone_mapping_methods.jpg'
$gradient=Join-Path $PSScriptRoot 'assets\srgb_oklab_gradient.png'
$msoFalse=0;$msoTrue=-1;$blank=12
function RGB([int]$r,[int]$g,[int]$b){$r+256*$g+65536*$b}
$navy=RGB 21 31 51;$cream=RGB 247 244 238;$coral=RGB 239 101 87;$ink=RGB 37 45 59;$white=RGB 255 255 255;$gray=RGB 108 117 131
function Text($s,$x,$y,$w,$h,$v,$size,$color,$bold=$false,$align=1){$o=$s.Shapes.AddTextbox(1,$x,$y,$w,$h);$o.TextFrame.TextRange.Text=$v;$o.TextFrame.TextRange.Font.Name='Aptos';$o.TextFrame.TextRange.Font.Size=$size;$o.TextFrame.TextRange.Font.Bold=$(if($bold){$msoTrue}else{$msoFalse});$o.TextFrame.TextRange.Font.Color.RGB=$color;$o.TextFrame.TextRange.ParagraphFormat.Alignment=$align;$o.TextFrame.MarginLeft=0;$o.TextFrame.MarginRight=0;$o.TextFrame.MarginTop=0;$o.TextFrame.MarginBottom=0;$o}
function Rect($s,$x,$y,$w,$h,$fill,$round=$false){$o=$s.Shapes.AddShape($(if($round){5}else{1}),$x,$y,$w,$h);$o.Fill.ForeColor.RGB=$fill;$o.Line.Visible=$msoFalse;$o}
function Base($s,$title,$num){$s.FollowMasterBackground=$msoFalse;$s.Background.Fill.ForeColor.RGB=$cream;Rect $s 0 0 960 10 $coral|Out-Null;Text $s 52 28 820 46 $title 28 $navy $true|Out-Null;Text $s 890 35 30 22 ('{0:00}' -f $num) 11 $gray $true 2|Out-Null}
function AddFittedPicture($s,$path,$x,$y,$w,$h){$p=$s.Shapes.AddPicture($path,$msoFalse,$msoTrue,$x,$y,-1,-1);$p.LockAspectRatio=$msoTrue;if(($p.Width/$p.Height)-gt($w/$h)){$p.Width=[single]$w;$p.Left=[single]$x;$p.Top=[single]($y+($h-$p.Height)/2)}else{$p.Height=[single]$h;$p.Top=[single]$y;$p.Left=[single]($x+($w-$p.Width)/2)};$p}
$ppt=New-Object -ComObject PowerPoint.Application;$ppt.Visible=$msoTrue;$pres=$ppt.Presentations.Open($file,0,0,0)
try{
  # First application slide: physically based rendering and display transform.
  $s=$pres.Slides.Item(14);for($i=$s.Shapes.Count;$i -ge 1;$i--){$s.Shapes.Item($i).Delete()};Base $s 'Цветовосприятие в компьютерном рендеринге' 14
  Rect $s 48 92 470 414 $white $true|Out-Null
  $text="В компьютерном рендеринге расчёт света должен учитывать различие между физической интенсивностью излучения и яркостью, воспринимаемой человеком. Уравнения освещения, смешение цветов и фильтрацию текстур выполняют в линейном RGB, где удвоение значения соответствует удвоению световой энергии. Если смешивать гамма-кодированные значения sRGB напрямую, полупрозрачные слои и края объектов получаются слишком тёмными. Поэтому текстуры декодируют в линейное пространство перед вычислениями, а готовый кадр кодируют для дисплея.`n`nФизически обоснованный рендеринг моделирует отражение света материалом с помощью спектральных или RGB-приближений. Метамеризм позволяет воспроизводить многие спектрально разные материалы тремя каналами, но RGB-модель не всегда точно передаёт интерференцию, флуоресценцию и эффект изменения цвета при другом освещении. Современный рендер может хранить яркости в HDR-формате, диапазон которого значительно шире возможностей обычного экрана. Tone mapping преобразует HDR-яркости в диапазон дисплея и старается сохранить различимость деталей в тенях и светах.`n`nГлобальные операторы применяют одну функцию ко всему кадру, а локальные дополнительно учитывают соседние области изображения. Их действие связано с адаптацией зрения и локальным контрастом, поэтому разные методы дают различное впечатление от одной сцены. Слишком сильное сжатие контраста делает изображение плоским, а чрезмерное локальное усиление создаёт ореолы. После tone mapping часто выполняют цветокоррекцию, преобразование охвата и настройку насыщенности. В результате правдоподобие компьютерной сцены зависит не только от модели освещения, но и от того, как финальное изображение согласовано с особенностями зрения и характеристиками дисплея."
  Text $s 68 112 430 374 $text 10 $ink|Out-Null
  AddFittedPicture $s $tone 535 132 390 310|Out-Null

  # Second application slide: perceptual operations in graphics and interfaces.
  $s=$pres.Slides.Add(15,$blank);Base $s 'Цветовосприятие в обработке изображений' 15
  Rect $s 48 92 470 414 $white $true|Out-Null
  $text="Знания о цветовосприятии применяются при цветокоррекции, построении градиентов, сжатии изображений и визуализации данных. Во многих алгоритмах RGB преобразуют в пространство, где светлота отделена от цветовых координат. Это позволяет изменять контраст, не вызывая нежелательного сдвига цветового тона. Модели CIELAB и Oklab стремятся сделать одинаковые числовые расстояния более близкими к одинаково заметным цветовым различиям.`n`nПри интерполяции непосредственно в гамма-кодированном sRGB середина градиента может оказаться темнее ожидаемого. Интерполяция в линейном RGB соответствует физическому смешению света, но не гарантирует равномерного зрительного изменения. Oklab удобен, когда требуется визуально плавный переход, а OkLCh позволяет отдельно управлять светлотой, насыщенностью и направлением изменения тона. Выбор пространства поэтому зависит от того, моделируется ли свет или создаётся последовательность, равномерная для наблюдателя.`n`nПерцептивные модели применяют и при оценке качества: метрики цветового различия ΔE помогают сравнивать исходное и обработанное изображение. В методах сжатия можно точнее сохранять компоненты, к которым зрение чувствительнее, и сильнее сокращать менее заметную информацию. При сегментации изображения переход из RGB в Lab иногда упрощает разделение областей по цвету и светлоте. В научной визуализации шкала должна изменяться монотонно по воспринимаемой светлоте, иначе ложные границы могут быть приняты за особенности данных. В интерфейсах цвет используют для группировки, выделения состояния и направления внимания, но значение нельзя кодировать только оттенком. Поэтому компьютерная графика использует модели зрения не как декоративное правило, а как основу для вычислений, сохраняющих различимость и предсказуемый внешний вид цвета."
  Text $s 68 112 430 374 $text 10 $ink|Out-Null
  AddFittedPicture $s $gradient 535 132 390 310|Out-Null

  for($n=16;$n -le $pres.Slides.Count;$n++){
    $sl=$pres.Slides.Item($n)
    for($i=1;$i -le $sl.Shapes.Count;$i++){
      $sh=$sl.Shapes.Item($i)
      if($sh.HasTextFrame -eq $msoTrue -and $sh.Left -gt 850 -and $sh.Top -lt 70){$sh.TextFrame.TextRange.Text=('{0:00}' -f $n)}
    }
  }
  $pres.Save()
}finally{$pres.Close();$ppt.Quit();[Runtime.InteropServices.Marshal]::ReleaseComObject($pres)|Out-Null;[Runtime.InteropServices.Marshal]::ReleaseComObject($ppt)|Out-Null;[GC]::Collect();[GC]::WaitForPendingFinalizers()}
