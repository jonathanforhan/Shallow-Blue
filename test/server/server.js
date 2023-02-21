import cors from 'cors';
import { Chess } from 'chess.js';
import { Engine } from './engine.js';
import express from 'express';
const app = express();
const PORT = 3001;

app.use(cors({ origin: true, credentials: true }));

app.get('/', (req, res) => {
  res.send('Welcome to Shallow Blue api')
})

app.get('/:id', (req, res) => {
  let fen = req.params.id.replaceAll('@', '/')
  console.log(fen)

  let game = new Chess();

  try {
    game = new Chess(fen);
  } catch(e) {
    res.json({ error: `${e}` }).status(401)
    return;
  }

  let engine = new Engine();

  const moves = game.moves();
  if(game.isGameOver() || game.isDraw() || moves.length === 0) {
    res.json({ error: 'Game Over' })
  }
  const i = Math.floor(Math.random() * moves.length);

  let m = engine.move(fen).split("-");
  try {
    game.move({ to: m[0], from:m[1]  });
  } catch(e) {
    console.log(e);
    res.json(moves[i]);
    return;
  }
  res.json({ to: m[0], from:m[1] });

})

app.listen(PORT, () => console.log(`Server listening on port ${PORT}`));
