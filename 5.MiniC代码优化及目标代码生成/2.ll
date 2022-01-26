; ModuleID = 'test'
source_filename = "test"

declare i32 @putchar(i32)

declare i32 @getchar()

define i32 @calc(i32 %k, i32 %t) {
entry:
  br label %ret

ret:                                              ; preds = %entry
  %mul = mul i32 %k, %t
  ret i32 %mul
}

define i32 @main() {
entry:
  %methodCall = call i32 @getchar()
  %sub = sub i32 %methodCall, 48
  %methodCall3 = call i32 @getchar()
  %sub5 = sub i32 %methodCall3, 48
  br label %condW

condW:                                            ; preds = %doW, %entry
  %target.0 = phi i32 [ 1, %entry ], [ %mul, %doW ]
  %i.0 = phi i32 [ 0, %entry ], [ %add, %doW ]
  %SLT = icmp slt i32 %i.0, %sub5
  %condValW = icmp ne i1 %SLT, false
  br i1 %condValW, label %doW, label %ntW

doW:                                              ; preds = %condW
  %add = add i32 %i.0, 1
  %mul = mul i32 %target.0, %sub
  br label %condW

ntW:                                              ; preds = %condW
  %add15 = add i32 %target.0, 48
  %methodCall16 = call i32 @putchar(i32 %add15)
  br label %ret

ret:                                              ; preds = %ntW
  ret i32 0
}
