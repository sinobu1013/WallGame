set canvas_size 700
set game_info_size 300

# キャンバス作成
set canvas_size_w [expr $canvas_size + 10 + $game_info_size]
set canvas_size_h [expr $canvas_size + 10]
canvas .board -width $canvas_size_w -height $canvas_size_h -bg "LightSkyBlue"

# ターン表示部分の初期化
set turn_text_x [expr $canvas_size + ($game_info_size / 2)]
set turn_text_y 25
.board create text $turn_text_x $turn_text_y -text "GAME START" -tags turn -font {{MS 明朝} 20}

# ボードの作成
set game_data [game_init]
set sum_square_w [lindex $game_data 3]
set sum_square_h [lindex $game_data 2]
set square_size_w [expr {int($canvas_size / $sum_square_w)}]
set square_size_h [expr {int($canvas_size / $sum_square_h)}]
for {set n 0; set y 0} {$y < $sum_square_h} {incr y} {
    set xs 15
    set ys [expr $y * $square_size_h + 10]
    set xe $canvas_size
    set ye [expr $y * $square_size_h + 10]

    for {set x 0} {$x < $sum_square_w} {incr x} {
        set xs [expr $x * $square_size_w + 10 + 5]
        set ys [expr $y * $square_size_h + 10 + 5]
        set xe [expr ($x + 1) * $square_size_w + 10 - 5]
        set ye [expr ($y + 1) * $square_size_h + 10 - 5]
        set tag_name [format "square_%d_%d" $x $y]

        # 各マスの作成
        set i [.board create rectangle $xs $ys $xe $ye -tags $tag_name -fill green]

        # 横軸方向の壁
        if {$y != [expr $sum_square_h - 1]} {
            set wall_tag_name [format "wall_w_%d_%d wall_w wall" $x $y]
            .board create rectangle $xs $ye $xe [expr $ye + 10] -tags $wall_tag_name -fill white
        }

        # 縦軸方向の壁
        if {$x != [expr $sum_square_w - 1]} {
            set wall_tag_name [format "wall_h_%d_%d wall_h wall" $x $y]
            .board create rectangle $xe $ys [expr $xe + 10] $ye -tags $wall_tag_name -fill white
        }
    }
}

# プレイヤー作成
set player_number [lindex $game_data 4]
for {set i 0} {$i < $player_number} {incr i} {
    set center_x [expr ([lindex $game_data [expr $i * 3 + 5]] + 0.5) * $square_size_w]
    set center_y [expr ([lindex $game_data [expr $i * 3 + 6]] + 0.5) * $square_size_h]
    set xs [expr {int($center_x - (($square_size_w * 0.8) / 2))} + 10]
    set ys [expr {int($center_y - (($square_size_h * 0.8) / 2))} + 10]
    set xe [expr {int($center_x + (($square_size_w * 0.8) / 2))} + 10]
    set ye [expr {int($center_y + (($square_size_h * 0.8) / 2))} + 10]

    if {$i == 0} {
        set color "#ffffff"
    } else {
        set color "#000000"
    }
    .board create oval $xs $ys $xe $ye -fill $color -tags player_$i
}

# ゲーム情報を表示部分
set main_text_x [expr $canvas_size + ($game_info_size / 2)]
set main_text_y 100
set main_rectangle_xs [expr $main_text_x - 75]
set main_rectangle_ys [expr $main_text_y - 25]
set main_rectangle_xe [expr $main_text_x + 75]
set main_rectangle_ye [expr $main_text_y + 25]
.board create rectangle $main_rectangle_xs $main_rectangle_ys $main_rectangle_xe $main_rectangle_ye -fill white -tags main_rectangle
.board create text $main_text_x $main_text_y -text "white turn" -tags main_player -font {{MS 明朝} 20} -fill black
.board itemconfigure turn -text "turn :[lindex $game_data 0]"

# ゲーム開始アニメーション
.board create rectangle 0 100 [expr $canvas_size_w] [expr $canvas_size_h - 100] -fill red -tags "game_start game_start_rectangle"
.board create text [expr $canvas_size_w / 2] [expr $canvas_size_h / 2] -text "Game START !!" -font {{MS 明朝} 100} -fill white -tags game_start

# 表示を薄くする（ゲーム開始アニメーション用）
proc fade_out {alpha} {
    if {$alpha > 0 } {
        # 色を薄くする
        set color [format "#%02x%02x%02x" [expr {int(255 * $alpha)}] 0 0]
        .board itemconfigure game_start_rectangle -fill $color
        after 100 [list fade_out [expr $alpha - 0.05]]
    } else {
        #四角形を削除
        delete_rectangle
    }
}
fade_out 1.0

# 四角形を削除（ゲーム開始アニメーション用）
proc delete_rectangle {} {
    .board delete game_start
}


pack .board



