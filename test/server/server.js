import cors from 'cors';
import { Chess } from 'chess.js';
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
  let game = {};
  try {
    game = new Chess(fen);
  } catch {
    res.json({ error: "Invalid Fen" }).status(401)
  }
  // add-on function(chess)
  res.json('e6')
})

app.listen(PORT, () => {
  console.log(`Server listening on port ${PORT}`)
})
