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

  let engine = new Engine();
  let game = {};

  try {
    game = new Chess(fen);
  } catch {
    res.json({ error: "Invalid Fen" }).status(401)
    return;
  }

  let m = engine.move(game.board());
  res.json(m)
})

app.listen(PORT, () => console.log(`Server listening on port ${PORT}`));
