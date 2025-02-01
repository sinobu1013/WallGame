set canvas_size 700
set game_info_size 300

canvas .board -width [expr $canvas_size + 10 + $game_info_size] -height [expr $canvas_size + 10]

set turn_text_x [expr $canvas_size + ($game_info_size / 2)]
set turn_text_y 25
.board create text $turn_text_x $turn_text_y -text "GAME START" -tags turn -font {{ＭＳ 明朝} 20}

set button_value 0

set button_font {{ＭＳ 明朝} 20}
set button_w 6
set up_button_x [expr $canvas_size + ($game_info_size / 2)]
set up_button_y [expr $canvas_size / 2 - 50]
set up_button [button .up_Button -text "UP" -width $button_w -bg red -font $button_font -command "push_button 1"]
.board create window $up_button_x $up_button_y -window $up_button
set left_button_x [expr $canvas_size + ($game_info_size / 2) -50]
set left_button_y [expr $canvas_size / 2 - 50 + 50]
set left_button [button .left_Button -text "LEFT" -width $button_w -bg red -font $button_font -command "push_button 4"]
.board create window $left_button_x $left_button_y -window $left_button
set right_button_x [expr $canvas_size + ($game_info_size / 2) + 50]
set right_button_y [expr $canvas_size / 2 - 50 + 50]
set right_button [button .right_Button -text "RIGHT" -width $button_w -bg red -font $button_font -command "push_button 3"]
.board create window $right_button_x $right_button_y -window $right_button
set down_button_x [expr $canvas_size + ($game_info_size / 2)]
set down_button_y [expr $canvas_size / 2 - 50 + 100]
set down_button [button .down_Button -text "DOWN" -width $button_w -bg red -font $button_font -command "push_button 2"]
.board create window $down_button_x $down_button_y -window $down_button

update idletasks
puts "up_button_size_h : [winfo height $up_button]"

set game_date [game_init]

set sum_square_w  [lindex $game_date 3]
set sum_square_h  [lindex $game_date 2]

puts "sum_square_w : $sum_square_w"

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

pack .board

set player_number [lindex $game_date 4]
for {set i 0} {$i < $player_number} {incr i} {
    set center_x [expr ([lindex $game_date [expr $i * 3 + 5]] + 0.5) * $square_size_w]
    set center_y [expr ([lindex $game_date [expr $i * 3 + 6]] + 0.5) * $square_size_h]
    set xs [expr {int($center_x - (($square_size_w * 0.8) / 2))} + 10]
    set ys [expr {int($center_y - (($square_size_h * 0.8) / 2))} + 10]
    set xe [expr {int($center_x + (($square_size_w * 0.8) / 2))} + 10]
    set ye [expr {int($center_y + (($square_size_h * 0.8) / 2))} + 10]

    if {$i == 0} {
        set color "#FFFFFF"
    } else {
        set color "#000000"
    }
    .board create oval $xs $ys $xe $ye -fill $color -tags player_$i
}

pack .board

.board itemconfigure turn -text "turn :[lindex $game_date 0]" -tags "turn"

pack .board


# ターンごとに実行される関数
proc draw_board {button_value} {
    set canvas_size 700
    set game_info_size 300

    set game_date [game_proc $button_value]

    set sum_square_w  [lindex $game_date 3]
    set sum_square_h  [lindex $game_date 2]

    set square_size_w [expr {int($canvas_size / $sum_square_w)}]
    set square_size_h [expr {int($canvas_size / $sum_square_h)}]

    pack .board
    set player_number [lindex $game_date 4]
    for {set i 0} {$i < $player_number} {incr i} {
        set center_x [expr ([lindex $game_date [expr $i * 3 + 5]] + 0.5) * $square_size_w]
        set center_y [expr ([lindex $game_date [expr $i * 3 + 6]] + 0.5) * $square_size_h]
        set xs [expr {int($center_x - (($square_size_w * 0.8) / 2))} + 10]
        set ys [expr {int($center_y - (($square_size_h * 0.8) / 2))} + 10]
        set xe [expr {int($center_x + (($square_size_w * 0.8) / 2))} + 10]
        set ye [expr {int($center_y + (($square_size_h * 0.8) / 2))} + 10]

        .board coords player_$i $xs $ys $xe $ye
    }

    pack .board

    .board itemconfigure turn -text "turn :[lindex $game_date 0]"

    pack .board
}

proc push_button {n} {
    global button_value
    set button_value $n
    draw_board $button_value
}

# クリック時のイベント関数
bind .board <Button-1> {
    set item_id [.board find withtag current]
    set tags [.board gettags $item_id]
    puts $tags

    # 特定のタグ名（"wall"）を持つか確認
    if {[lsearch $tags "wall"] >= 0} {
        # タグをアンダースコアで分割

        if {[lsearch $tags "wall_w"] >= 0} {
            set parts [split [lindex $tags 0] "_"]
            # 分割した結果から座標を取得
            set xt [lindex $parts 2]
            set yt [lindex $parts 3]
            set xt [expr {$xt + 1}]
            set yt [expr {$yt}]

            set puls_tag_name "wall_w_$xt"
            append puls_tag_name "_$yt"
            puts $puls_tag_name
            .board itemconfig [lindex $tags 0] -fill red
            .board itemconfig $puls_tag_name -fill red
            create_wall [lindex $tags 0] $puls_tag_name
        }
        if {[lsearch $tags "wall_h"] >= 0} {
            set parts [split [lindex $tags 0] "_"]
            # 分割した結果から座標を取得
            set xt [lindex $parts 2]
            set yt [lindex $parts 3]
            set xt [expr {$xt}]
            set yt [expr {$yt + 1}]

            set puls_tag_name "wall_h_$xt"
            append puls_tag_name "_$yt"
            puts $puls_tag_name
            .board itemconfig [lindex $tags 0] -fill red
            .board itemconfig $puls_tag_name -fill red
        }
    }
}