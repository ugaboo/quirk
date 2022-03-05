; ModuleID = 'module'
source_filename = "module"

define void @bar() {
  ret void
}

define i64 @foo() {
  ret i64 42
}

define i32 @main() {
  ret i64 0
  ret i32 0
}
