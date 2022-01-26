; ModuleID = 'test'
source_filename = "test"

declare i32 @putchar(i32)

declare i32 @getchar()

define i32 @calc(i32 %k, i32 %t) {
entry:
  %t2 = alloca i32
  %k1 = alloca i32
  store i32 %k, i32* %k1
  store i32 %t, i32* %t2
  br label %ret

ret:                                              ; preds = %entry
  %load = load i32, i32* %k1
  %load3 = load i32, i32* %t2
  %mul = mul i32 %load, %load3
  ret i32 %mul
}

define i32 @main() {
entry:
  %a = alloca i32
  store i32 0, i32* %a
  %b = alloca i32
  store i32 0, i32* %b
  %i = alloca i32
  store i32 0, i32* %i
  %target = alloca i32
  store i32 1, i32* %target
  %load = load i32, i32* %a
  %methodCall = call i32 @getchar()
  store i32 %methodCall, i32* %a
  %load1 = load i32, i32* %a
  store i32 48, i32* %a
  %load2 = load i32, i32* %b
  %methodCall3 = call i32 @getchar()
  store i32 %methodCall3, i32* %b
  %load4 = load i32, i32* %b
  store i32 48, i32* %b
  %load5 = load i32, i32* %i
  store i32 0, i32* %i
  br label %condW

condW:                                            ; preds = %doW, %entry
  %load6 = load i32, i32* %i
  %load7 = load i32, i32* %b
  %SLT = icmp slt i32 %load6, %load7
  %condValW = icmp ne i1 %SLT, false
  br i1 %condValW, label %doW, label %ntW

doW:                                              ; preds = %condW
  %load8 = load i32, i32* %i
  %load9 = load i32, i32* %i
  %add = add i32 %load9, 1
  store i32 %add, i32* %i
  %load10 = load i32, i32* %target
  %load11 = load i32, i32* %target
  %load12 = load i32, i32* %a
  %mul = mul i32 %load11, %load12
  store i32 %mul, i32* %target
  br label %condW

ntW:                                              ; preds = %condW
  %load13 = load i32, i32* %target
  %add14 = add i32 %load13, 48
  %methodCall15 = call i32 @putchar(i32 %add14)
  br label %ret

ret:                                              ; preds = %ntW
  ret i32 0
}
