; ModuleID = 'test.txt'
source_filename = "test"

declare i32 @putchar(i32)

declare i32 @getchar()

define i32 @calc(i32 %k, i32 %t) {
entry:
  br label %ret

ret:                                              ; preds = %entry
  %multmp = mul i32 %k, %t
  ret i32 %multmp
}

define i32 @main() {
entry:
  %calltmp = call i32 @getchar()
  %minustmp = sub i32 %calltmp, 48
  %calltmp4 = call i32 @getchar()
  %minustmp6 = sub i32 %calltmp4, 48
  br label %cond

cond:                                             ; preds = %compstcont, %entry
  %target.0 = phi i32 [ 1, %entry ], [ %multmp, %compstcont ]
  %i.0 = phi i32 [ 0, %entry ], [ %addtmp, %compstcont ]
  %ltmp = icmp ult i32 %i.0, %minustmp6
  %cond10 = icmp ne i1 %ltmp, false
  br i1 %cond10, label %loop, label %whilecont

loop:                                             ; preds = %cond
  br label %compst

compst:                                           ; preds = %loop
  %addtmp = add i32 %i.0, 1
  %multmp = mul i32 %target.0, %minustmp
  br label %compstcont

compstcont:                                       ; preds = %compst
  br label %cond

whilecont:                                        ; preds = %cond
  %addtmp17 = add i32 %target.0, 48
  %calltmp18 = call i32 @putchar(i32 %addtmp17)
  br label %ret

ret:                                              ; preds = %whilecont
  ret i32 0
}
