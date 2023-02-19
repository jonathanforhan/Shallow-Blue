const require = createRequire(import.meta.url);
import { createRequire } from "module";
const { move } = require('../../engine/bin/debug/shallow_blue.node');

export class Engine {
  /**
   * @param {string} fen - the fen string that will be decoded in C++ add-on
   */
  move(fen) {
    return move(fen)
  }
}
