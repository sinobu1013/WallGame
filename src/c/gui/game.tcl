# 初期状態でのゲーム情報の取得ができていないため、タグ名などをグローバル変数として使用できない問題が発生
# tclファイルのリファクタリングと初期化用のコマンドの作成を行なう
# 現状：クリックした際のタグ名取得ができていない
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

proc draw_board {button_value} {
    set canvas_size 700
    set game_info_size 300
    puts "button_value : $button_value"

    set game_date [game_proc $button_value]

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
                set wall_tag_name [format "wall_%d_%d" $xs $ye]
                .board create rectangle $xs $ye $xe [expr $ye + 10] -tags wall_tag_name
            }

            # 縦軸方向の壁
            if {$x != [expr $sum_square_w - 1]} {
                set wall_tag_name [format "wall_%d_%d" $xe $ys]
                .board create rectangle $xe $ys [expr $xe + 10] $ye -tags wall_tag_name
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
        .board create oval $xs $ys $xe $ye -fill $color
    }

    pack .board

    .board itemconfigure turn -text "turn :[lindex $game_date 0]"

    pack .board

    #after 1000 draw_board

}

proc push_button {n} {
    global button_value
    set button_value $n
    draw_board $button_value
}

# クリック時のイベント関数
bind .board <Button-1> {
    set x %x
    set y %y
    set itme_id [.board find closest $x $y]
    # 図形が存在する場合、タグを取得
    if {$item_id ne ""} {
        set tags [.board gettags $item_id]
        puts "Clicked on item with tags: $tags"
    } else {
        puts "No item found at clicked position."
    }
}

draw_board 0

