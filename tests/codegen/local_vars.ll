; ModuleID = 'module'
source_filename = "module"

define void @foo() {
  %1 = alloca i64, align 8
  %2 = alloca i64, align 8
  store i64 1, i64* %1, align 4
  %a = load i64, i64* %1, align 4
  store i64 %a, i64* %2, align 4
  ret i32 0
}

define i32 @main() {
}
