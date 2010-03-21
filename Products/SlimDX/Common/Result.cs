using System;

namespace SlimDX {
    public struct Result {
        public Result( int code )
            : this() {
            Code = code;
        }

        public int Code {
            get;
            private set;
        }

        public bool IsSuccess {
            get {
                // This is equivalent to the native SUCCEEDED macro.
                return Code >= 0;
            }
        }

        public bool IsFailure {
            get {
                // This is equivalent to the native FAILED macro.
                return Code < 0;
            }
        }

        public static Result Last {
            get {
                return last;
            }
        }

        public static void SetLast( Result result ) {
            last = result;
        }

        [ThreadStatic]
        static Result last;
    }
}