const SERVER_PORT = '3001';
const SERVER_URI = 'http://localhost:';

/**
 * @param {string} fen
 * @returns {string} res
 */
export default async function fetchMove(fen) {
  return fetch(SERVER_URI + SERVER_PORT + '/' + fen.replaceAll('/', '@'), {
    method: 'GET',
    headers: {
      'Content-Type': 'application/json',
    },
    credentials: 'include',
  })
  .then(res => res.json())
}
