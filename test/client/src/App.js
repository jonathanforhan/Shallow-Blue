import './App.css';
import { useState, useRef } from 'react';
import { Chessboard } from 'react-chessboard';
import { Chess } from 'chess.js'
import SideMenu from './components/SideMenu';
import useWindowDimensions from './util/useWindowDimensions';
import fetchMove from './util/fetchMove';

function App() {
  const _window = useWindowDimensions();

  const [game, setGame] = useState(new Chess());
  const [currentTimeout, setCurrentTimeout] = useState();
  const chessboardRef = useRef(null);

  const [position, setPosition] = useState();

  function safeGameMutate(modify) {
    setGame((g) => {
      const update = Object.assign(Object.create(Object.getPrototypeOf(g)), g);
      modify(update);
      return update;
    });
  }

  async function oppTurn() {
    console.log(game.fen())
    await fetchMove(game.fen()).then((move) => {
      safeGameMutate(g => g.move(move))
    });
  }

  function onDrop(src, dst) {
    // gameCopy is deep copy that maintains prototype
    let gameCopy = Object.assign(Object.create(Object.getPrototypeOf(game)), game);
    try {
      gameCopy.move({
        from: src,
        to: dst,
        promotion: "q",
      });
    } catch {
      return false;
    }
    setGame(gameCopy)
    const newTimeout = setTimeout(oppTurn, 400);
    setCurrentTimeout(newTimeout);

    return true;
  }

  return (
    <div className='App flex justify-center bg-slate-700 py-20 h-[100vh]'>
      <div className='ChessboardWrapper'>
        <Chessboard
          id='chessBoard'
          position={game.fen()}
          getPositionObject={setPosition}
          onPieceDrop={onDrop}
          arePremovesAllowed={true}
          boardWidth={_window.height - 160}
          customBoardStyle={{
            borderRadius: "4px",
            boxShadow: "0 2px 10px rgba(0, 0, 0, 0.5)",
          }}
          customDarkSquareStyle={{ backgroundColor: "#779952" }}
          customLightSquareStyle={{ backgroundColor: "#edeed1" }}
          
        />
      </div>
      <SideMenu
        safeGameMutate={safeGameMutate}
        chessboardRef={chessboardRef}
        currentTimeout={currentTimeout}
      />
      </div>
  );
}

export default App;
