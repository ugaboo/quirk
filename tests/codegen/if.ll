; ModuleID = 'module'
source_filename = "module"

@a = common global i64 0
@b = common global i64 0

define i32 @main() {
  store i64 1, i64* @a, align 4
  %a = load i64, i64* @a, align 4
  %icmp = icmp eq i64 %a, 1
  br i1 %icmp, label %then, label %else

then:                                             ; preds = %0
  store i64 1, i64* @b, align 4
  br label %end

else:                                             ; preds = %0
  %a1 = load i64, i64* @a, align 4
  %icmp2 = icmp eq i64 %a1, 2
  br i1 %icmp2, label %then3, label %else4

then3:                                            ; preds = %else
  store i64 2, i64* @b, align 4
  br label %end

else4:                                            ; preds = %else
  %a5 = load i64, i64* @a, align 4
  %icmp6 = icmp eq i64 %a5, 3
  br i1 %icmp6, label %then7, label %else8

then7:                                            ; preds = %else4
  store i64 3, i64* @b, align 4
  br label %end

else8:                                            ; preds = %else4
  store i64 0, i64* @b, align 4
  br label %end

end:                                              ; preds = %else8, %then7, %then3, %then
  ret i32 0
}
