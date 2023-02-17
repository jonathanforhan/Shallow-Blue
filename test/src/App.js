import './App.css';
import { useState } from 'react';
import { Chessboard } from 'react-chessboard'
import useWindowDimensions from './components/util/useWindowDimensions'

const App = () => {
  const { width, height } = useWindowDimensions();
  const [boardPosition, setBoardPosition] = useState(null);
  const handleBoardPosition = (e) => {
    setBoardPosition(e);
    console.log(e);
  }

  return (
    <div className='App flex justify-center bg-slate-700'>
      <div className='ChessboardWrapper'>
        <Chessboard
          boardWidth={height}
          getPositionObject={handleBoardPosition}

        />
      </div>
    </div>
  );
}

export default App;
