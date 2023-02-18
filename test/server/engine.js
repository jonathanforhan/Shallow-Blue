const require = createRequire(import.meta.url);
import { createRequire } from "module";
const { move } = require('../../engine/bin/debug/shallow_blue.node');

export class Engine {
  move(args) {
    return move(args)
  }
}
