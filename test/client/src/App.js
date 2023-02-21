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

  /**
   * @param {function} modify - modify function for the game Object
   * @returns {Object} update - updated game Object
   */
  function safeGameMutate(modify) {
    setGame((g) => {
      const update = new Chess(g.fen());
      modify(update);
      return update;
    });
  }

  /**
   * @param {string} fen - fen notation of current position
   */
  function oppTurn(fen) {
    fetchMove(fen).then((move) => {
      if(move.error) {
        alert('Game Over')
        return
      }
      safeGameMutate(g => g.move(move))
    })
  }

  /**
   * @param {string, string} src, dst - src square and destination dquare
   * @returns {boolean} - validity of move
   */
  function onDrop(src, dst) {
    let gameCopy = new Chess(game.fen());
    try {
      gameCopy.move({
        from: src,
        to: dst,
        promotion: "q",
      });
    } catch {
      return false;
    }
    console.log(gameCopy.fen())

    setGame(gameCopy);
    const newTimeout = setTimeout(oppTurn(gameCopy.fen()), 0);
    setCurrentTimeout(newTimeout);

    return true;
  }

  return (
    <div className='App flex justify-center bg-slate-700 py-20 h-[100vh]'>
      <div className='ChessboardWrapper'>
        <Chessboard
          id='chessBoard'
          position={game.fen()}
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
