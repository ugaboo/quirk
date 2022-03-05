; ModuleID = 'module'
source_filename = "module"

@y = common global i64 0

define i32 @main() {
  %1 = call i64 @foo(i64 101)
  %2 = call i64 @foo(i64 42)
  store i64 %2, i64* @y, align 4
  ret i32 0
}

define i64 @foo(i64 %x) {
  ret i64 %x
}
